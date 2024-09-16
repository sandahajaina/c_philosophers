/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sranaivo <sranaivo@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 14:04:51 by sranaivo          #+#    #+#             */
/*   Updated: 2024/09/16 17:16:31 by sranaivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check_simulation_running(t_philosopher *philosopher)
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

long long	current_timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ph_usleep(t_philosopher *philosopher, int sleep_time)
{
	long long	start;

	start = current_timestamp();
	while ((current_timestamp() - start) < (long long)sleep_time)
	{
		if (check_simulation_running(philosopher))
			return ;
		usleep(50);
	}
}

int	ph_atoi(const char *nptr)
{
	int	sign;
	int	i;
	int	nb;

	i = 0;
	sign = 1;
	nb = 0;
	while (nptr[i] == ' ' || nptr[i] == '\n' || nptr[i] == '\t'
		|| nptr[i] == '\v' || nptr[i] == '\f' || nptr[i] == '\r')
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign *= -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		nb = nb * 10 + nptr[i] - '0';
		i++;
	}
	return (nb * sign);
}
