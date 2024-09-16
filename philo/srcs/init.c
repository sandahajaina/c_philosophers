/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sranaivo <sranaivo@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 13:55:34 by sranaivo          #+#    #+#             */
/*   Updated: 2024/09/16 17:17:09 by sranaivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	init_philosophers(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->number_philo)
	{
		table->philosophers[i].table = table;
		table->philosophers[i].id = i + 1;
		table->philosophers[i].left_fork = i;
		table->philosophers[i].right_fork = (i + 1) % table->number_philo;
		pthread_mutex_init(&table->philosophers[i].m_last_meal_time, NULL);
		pthread_mutex_init(&table->philosophers[i].m_meals_eaten, NULL);
		pthread_mutex_init(&table->philosophers[i].m_start_time, NULL);
		table->philosophers[i].meals_eaten = 0;
		table->philosophers[i].start_time = current_timestamp();
	}
}

void	init_table(t_table *table, int argc, char **argv)
{
	int	i;

	table->number_philo = ph_atoi(argv[1]);
	table->time_to_die = ph_atoi(argv[2]);
	table->time_to_eat = ph_atoi(argv[3]);
	table->time_to_sleep = ph_atoi(argv[4]);
	if (argc == 6)
		table->number_meals_required = ph_atoi(argv[5]);
	else
		table->number_meals_required = -1;
	table->simulation_running = 1;
	i = -1;
	pthread_mutex_init(&table->print_mutex, NULL);
	pthread_mutex_init(&table->simulation_mutex, NULL);
	init_fork(table);
	i = -1;
	init_philosophers(table);
	pthread_mutex_init(&table->print_mutex, NULL);
}

void	init_fork(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->number_philo)
	{
		table->forks[i].id = i;
		pthread_mutex_init(&table->forks[i].mutex, NULL);
		i++;
	}
}

void	create_philosopher_threads(t_table *table)
{
	int			i;
	pthread_t	monitor_thread;

	i = -1;
	table->start_time = current_timestamp();
	while (++i < table->number_philo)
	{
		table->philosophers[i].last_meal_time = current_timestamp();
		pthread_create(&table->philosophers[i].thread, NULL,
			philosopher_routine, &table->philosophers[i]);
	}
	pthread_create(&monitor_thread, NULL, monitoring_routine, table);
	pthread_join(monitor_thread, NULL);
	i = 0;
	while (i < table->number_philo)
	{
		pthread_join(table->philosophers[i].thread, NULL);
		i++;
	}
}

void	cleanup_table(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->number_philo)
	{
		pthread_mutex_destroy(&table->forks[i].mutex);
	}
	pthread_mutex_destroy(&table->print_mutex);
	pthread_mutex_destroy(&table->simulation_mutex);
}
