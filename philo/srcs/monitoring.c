/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sranaivo <sranaivo@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 16:57:49 by sranaivo          #+#    #+#             */
/*   Updated: 2024/09/16 17:02:38 by sranaivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	check_all_philosophers_full(t_table *table,
		int *all_philosophers_full)
{
	if (table->number_meals_required != -1 && *all_philosophers_full)
	{
		pthread_mutex_lock(&table->simulation_mutex);
		table->simulation_running = 0;
		pthread_mutex_unlock(&table->simulation_mutex);
		return (1);
	}
	return (0);
}

static int	check_philo_death(t_table *table, int *i)
{
	pthread_mutex_lock(&table->philosophers[*i].m_last_meal_time);
	if (current_timestamp()
		- table->philosophers[*i].last_meal_time > table->time_to_die)
	{
		pthread_mutex_lock(&table->simulation_mutex);
		table->simulation_running = 0;
		printf("%lld %d died\n", (current_timestamp() - table->start_time),
			table->philosophers[*i].id);
		pthread_mutex_unlock(&table->simulation_mutex);
		pthread_mutex_unlock(&table->philosophers[*i].m_last_meal_time);
		return (1);
	}
	pthread_mutex_unlock(&table->philosophers[*i].m_last_meal_time);
	return (0);
}

static void	check_number_meals_required(t_table *table,
		int *all_philosophers_full, int *i)
{
	pthread_mutex_lock(&table->philosophers[*i].m_meals_eaten);
	if (table->number_meals_required != -1
		&& table->philosophers[*i].meals_eaten < table->number_meals_required)
	{
		pthread_mutex_unlock(&table->philosophers[*i].m_meals_eaten);
		*all_philosophers_full = 0;
	}
	else
		pthread_mutex_unlock(&table->philosophers[*i].m_meals_eaten);
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
			if (check_philo_death(table, &i))
				return (NULL);
			check_number_meals_required(table, &all_philosophers_full, &i);
			i++;
		}
		if (check_all_philosophers_full(table, &all_philosophers_full))
			return (NULL);
		usleep(1000);
	}
}
