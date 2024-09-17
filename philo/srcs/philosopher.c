/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sranaivo <sranaivo@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 17:05:23 by sranaivo          #+#    #+#             */
/*   Updated: 2024/09/17 10:31:21 by sranaivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*philosopher_routine(void *arg)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher *)arg;
	if (philosopher->id % 2 == 0)
		usleep(500);
	while (!check_simulation_running(philosopher))
	{
		eat(philosopher);
		ph_sleep(philosopher);
		think(philosopher);
	}
	return (NULL);
}

void	think(t_philosopher *philosopher)
{
	print_status(philosopher, "is thinking");
	if (philosopher->table->number_philo % 2 != 0)
	{
		ph_usleep(philosopher, ((philosopher->table->time_to_eat * 2)
				- philosopher->table->time_to_sleep));
	}
	usleep(100);
}

void	eat(t_philosopher *philosopher)
{
	if (!(take_forks(philosopher)))
		return ;
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

void	ph_sleep(t_philosopher *philosopher)
{
	print_status(philosopher, "is sleeping");
	ph_usleep(philosopher, philosopher->table->time_to_sleep);
}

int	take_forks(t_philosopher *philosopher)
{
	if (check_simulation_running(philosopher))
		return (0);
	if (philosopher->table->number_philo == 1)
	{
		take_left_fork(philosopher);
		pthread_mutex_lock(&philosopher->table->simulation_mutex);
		philosopher->table->simulation_running = 0;
		pthread_mutex_unlock(&philosopher->table->simulation_mutex);
		pthread_mutex_unlock(&philosopher->table->forks[0].mutex);
		return (0);
	}
	if (philosopher->id % 2 == 0)
	{
		take_left_fork(philosopher);
		take_right_fork(philosopher);
	}
	else
	{
		take_right_fork(philosopher);
		take_left_fork(philosopher);
	}
	return (1);
}
