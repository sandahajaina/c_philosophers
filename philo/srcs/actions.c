/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sranaivo <sranaivo@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 17:13:46 by sranaivo          #+#    #+#             */
/*   Updated: 2024/09/17 10:14:26 by sranaivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	take_left_fork(t_philosopher *philosopher)
{
	int	left;

	left = philosopher->left_fork;
	pthread_mutex_lock(&philosopher->table->forks[left].mutex);
	if (check_simulation_running(philosopher))
		return ;
	print_status(philosopher, "has taken a fork");
}

void	take_right_fork(t_philosopher *philosopher)
{
	int	right;

	right = philosopher->right_fork;
	pthread_mutex_lock(&philosopher->table->forks[right].mutex);
	if (check_simulation_running(philosopher))
		return ;
	print_status(philosopher, "has taken a fork");
}

void	put_down_forks(t_philosopher *philosopher)
{
	int	left;
	int	right;

	left = philosopher->left_fork;
	right = philosopher->right_fork;
	if (philosopher->id % 2 == 0)
	{
		pthread_mutex_unlock(&philosopher->table->forks[left].mutex);
		pthread_mutex_unlock(&philosopher->table->forks[right].mutex);
	}
	else
	{
		pthread_mutex_unlock(&philosopher->table->forks[right].mutex);
		pthread_mutex_unlock(&philosopher->table->forks[left].mutex);
	}
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
