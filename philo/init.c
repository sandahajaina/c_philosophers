/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sranaivo <sranaivo@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 13:55:34 by sranaivo          #+#    #+#             */
/*   Updated: 2024/09/13 17:04:35 by sranaivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	while (++i < table->number_philo)
	{
		table->philosophers[i].table = table;
		table->philosophers[i].id = i + 1;
		table->philosophers[i].left_fork = i;
		table->philosophers[i].right_fork = (i + 1) % table->number_philo;
		pthread_mutex_init(&table->philosophers[i].m_state, NULL);
		pthread_mutex_init(&table->philosophers[i].m_last_meal_time, NULL);
		pthread_mutex_init(&table->philosophers[i].m_meals_eaten, NULL);
		pthread_mutex_init(&table->philosophers[i].m_start_time, NULL);
		table->philosophers[i].state = 0;
		table->philosophers[i].meals_eaten = 0;
		table->philosophers[i].start_time = current_timestamp();
	}
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

void	*philosopher_routine(void *arg)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher *)arg;
	if (philosopher->id % 2 != 0)
		usleep(500);
	while (!check_philo_death(philosopher))
	{
		eat(philosopher);
		ph_sleep(philosopher);
		think(philosopher);
	}
	return (NULL);
}

int	check_philo_death(t_philosopher *philosopher)
{
	pthread_mutex_lock(&philosopher->table->simulation_mutex);
	if (!(philosopher->table->simulation_running))
	{
		pthread_mutex_unlock(&philosopher->table->simulation_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philosopher->table->simulation_mutex);
	return (0);
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

void	*monitoring_routine(void *arg)
{
	t_table	*table;
	int		i;
	int		all_philosophers_full;

	table = (t_table *)arg;
	while (1)
	{
		i = 0;
		all_philosophers_full = 1;
		while (i < table->number_philo)
		{
			pthread_mutex_lock(&table->philosophers[i].m_last_meal_time);
			if (current_timestamp()
				- table->philosophers[i].last_meal_time > table->time_to_die)
			{
				pthread_mutex_lock(&table->simulation_mutex);
				table->simulation_running = 0;
				printf("%lld %d died\n", (current_timestamp()
						- table->start_time), table->philosophers[i].id);
				pthread_mutex_unlock(&table->simulation_mutex);
				pthread_mutex_unlock(&table->philosophers[i].m_last_meal_time);
				return (NULL);
			}
			pthread_mutex_unlock(&table->philosophers[i].m_last_meal_time);
			pthread_mutex_lock(&table->philosophers[i].m_meals_eaten);
			if (table->number_meals_required != -1
				&& table->philosophers[i].meals_eaten < table->number_meals_required)
			{
				pthread_mutex_unlock(&table->philosophers[i].m_meals_eaten);
				all_philosophers_full = 0;
			}
			else
				pthread_mutex_unlock(&table->philosophers[i].m_meals_eaten);
			i++;
		}
		if (table->number_meals_required != -1 && all_philosophers_full)
		{
			pthread_mutex_lock(&table->simulation_mutex);
			table->simulation_running = 0;
			pthread_mutex_unlock(&table->simulation_mutex);
			return (NULL);
		}
		usleep(1000);
	}
}

void	cleanup_table(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->number_philo)
	{
		pthread_mutex_destroy(&table->forks[i].mutex);
		pthread_mutex_destroy(&table->philosophers[i].m_state);
	}
	pthread_mutex_destroy(&table->print_mutex);
	pthread_mutex_destroy(&table->simulation_mutex);
}

void	print_status(t_philosopher *philosopher, char *message)
{
	pthread_mutex_lock(&philosopher->table->print_mutex);
	pthread_mutex_lock(&philosopher->table->simulation_mutex);
	if (philosopher->table->simulation_running)
	{
		printf("%lld %d %s\n", (current_timestamp()
				- philosopher->table->start_time), philosopher->id, message);
	}
	pthread_mutex_unlock(&philosopher->table->simulation_mutex);
	pthread_mutex_unlock(&philosopher->table->print_mutex);
}

void	take_left_fork(t_philosopher *philosopher)
{
	pthread_mutex_lock(&philosopher->table->forks[philosopher->left_fork].mutex);
	if (check_philo_death(philosopher))
		return ;
	print_status(philosopher, "has taken a fork");
}

void	take_right_fork(t_philosopher *philosopher)
{
	pthread_mutex_lock(&philosopher->table->forks[philosopher->right_fork].mutex);
	if (check_philo_death(philosopher))
		return ;
	print_status(philosopher, "has taken a fork");
}

void	take_forks(t_philosopher *philosopher)
{
	if (check_philo_death(philosopher))
		return ;
	if (philosopher->left_fork < philosopher->right_fork)
	{
		take_left_fork(philosopher);
		take_right_fork(philosopher);
	}
	else
	{
		take_right_fork(philosopher);
		take_left_fork(philosopher);
	}
}

void	think(t_philosopher *philosopher)
{
	set_philo_state(philosopher, THINKING);
	print_status(philosopher, "is thinking");
	usleep(1);
}

void	put_down_forks(t_philosopher *philosopher)
{
	pthread_mutex_unlock(&philosopher->table->forks[philosopher->right_fork].mutex);
	pthread_mutex_unlock(&philosopher->table->forks[philosopher->left_fork].mutex);
}

void	eat(t_philosopher *philosopher)
{
	take_forks(philosopher);
	set_philo_state(philosopher, EATING);
	pthread_mutex_lock(&philosopher->m_last_meal_time);
	philosopher->last_meal_time = current_timestamp();
	pthread_mutex_unlock(&philosopher->m_last_meal_time);
	print_status(philosopher, "is eating");
	pthread_mutex_lock(&philosopher->m_meals_eaten);
	philosopher->meals_eaten++;
	pthread_mutex_unlock(&philosopher->m_meals_eaten);
	ph_usleep(philosopher, philosopher->table->time_to_eat);
	put_down_forks(philosopher);
}

void	set_philo_state(t_philosopher *philosopher, t_state state)
{
	pthread_mutex_lock(&philosopher->m_state);
	philosopher->state = state;
	pthread_mutex_unlock(&philosopher->m_state);
}

void	ph_sleep(t_philosopher *philosopher)
{
	set_philo_state(philosopher, SLEEPING);
	print_status(philosopher, "is sleeping");
	ph_usleep(philosopher, philosopher->table->time_to_sleep);
}

void	ph_usleep(t_philosopher *philosopher, int sleep_time)
{
	long long	start;

	start = current_timestamp();
	if (check_philo_death(philosopher))
		return ;
	while ((current_timestamp() - start) < (long long)sleep_time)
	{
		usleep(50);
	}
}
