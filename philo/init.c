/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sranaivo <sranaivo@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 13:55:34 by sranaivo          #+#    #+#             */
/*   Updated: 2024/09/09 17:02:42 by sranaivo         ###   ########.fr       */
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
	table->forks = malloc(sizeof(pthread_mutex_t) * table->number_philo);
	table->philosophers = malloc(sizeof(t_philosopher) * table->number_philo);
	table->simulation_running = 1;
	i = -1;
	while (++i < table->number_philo)
		pthread_mutex_init(&table->forks[i], NULL);
	pthread_mutex_init(&table->print_mutex, NULL);
	pthread_mutex_init(&table->simulation_mutex, NULL);
	i = -1;
	while (++i < table->number_philo)
	{
		table->philosophers[i].table = table;
		table->philosophers[i].id = i + 1;
		table->philosophers[i].left_fork = &table->forks[i];
		table->philosophers[i].right_fork = &table->forks[(i + 1)
			% table->number_philo];
		pthread_mutex_init(&table->philosophers[i].state_mutex, NULL);
		pthread_mutex_init(&table->philosophers[i].meal_mutex, NULL);
		table->philosophers[i].state = 0;
		table->philosophers[i].meals_eaten = 0;
	}
	pthread_mutex_init(&table->print_mutex, NULL);
}

void	*philosopher_routine(void *arg)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher *)arg;
	while (1)
	{
		pthread_mutex_lock(&philosopher->table->simulation_mutex);
        if (!(philosopher->table->simulation_running)) {
            pthread_mutex_unlock(&philosopher->table->simulation_mutex);
            break;
        }
        pthread_mutex_unlock(&philosopher->table->simulation_mutex);
		eat(philosopher);
		ph_sleep(philosopher);
		think(philosopher);
	}
	return (NULL);
}

int	has_died(t_philosopher *philosopher)
{
	return (current_timestamp()
		- philosopher->last_meal_time > philosopher->table->time_to_die);
}

void	create_philosopher_threads(t_table *table)
{
	int	i;
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

void *monitoring_routine(void *arg) {
    t_table *table = (t_table *)arg;
    int i;

    while (1) {
        i = 0;
        while (i < table->number_philo) {
            pthread_mutex_lock(&table->simulation_mutex);
			pthread_mutex_lock(&table->philosophers[i].meal_mutex);
            if (current_timestamp() - table->philosophers[i].last_meal_time > table->time_to_die) {
				pthread_mutex_unlock(&table->philosophers[i].meal_mutex);
				table->simulation_running = 0;
				printf("%lld %d died\n", (current_timestamp() - table->start_time), table->philosophers[i].id);
                pthread_mutex_unlock(&table->simulation_mutex);
                return NULL;
            }
			pthread_mutex_unlock(&table->philosophers[i].meal_mutex);
            pthread_mutex_unlock(&table->simulation_mutex);
            i++;
        }
        usleep(100);
    }
}


void	cleanup_table(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->number_philo)
	{
		pthread_mutex_destroy(&table->forks[i]);
		pthread_mutex_destroy(&table->philosophers[i].state_mutex);
	}
	pthread_mutex_destroy(&table->print_mutex);
	pthread_mutex_destroy(&table->simulation_mutex);
	free(table->forks);
	free(table->philosophers);
}

void take_left_fork(t_philosopher *philosopher)
{
	pthread_mutex_lock(philosopher->left_fork);
	pthread_mutex_lock(&philosopher->table->print_mutex);
	printf("%lld %d has taken a fork\n", (current_timestamp() - philosopher->table->start_time), philosopher->id);
	pthread_mutex_unlock(&philosopher->table->print_mutex);
}

void take_right_fork(t_philosopher *philosopher)
{
	pthread_mutex_lock(philosopher->right_fork);
	pthread_mutex_lock(&philosopher->table->print_mutex);
	printf("%lld %d has taken a fork\n", (current_timestamp() - philosopher->table->start_time), philosopher->id);
	pthread_mutex_unlock(&philosopher->table->print_mutex);
}

void	take_forks(t_philosopher *philosopher)
{
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
	pthread_mutex_lock(&philosopher->table->print_mutex);
	printf("%lld %d is thinking\n", (current_timestamp() - philosopher->table->start_time), philosopher->id);
	pthread_mutex_unlock(&philosopher->table->print_mutex);
}

void	put_down_forks(t_philosopher *philosopher)
{
    pthread_mutex_unlock(philosopher->right_fork);
    pthread_mutex_unlock(philosopher->left_fork);
}

void	eat(t_philosopher *philosopher)
{
	take_forks(philosopher);
	pthread_mutex_lock(&philosopher->table->print_mutex);
	printf("%lld %d is eating\n", (current_timestamp() - philosopher->table->start_time), philosopher->id);
	pthread_mutex_unlock(&philosopher->table->print_mutex);
	pthread_mutex_lock(&philosopher->meal_mutex);
	philosopher->last_meal_time = current_timestamp();
	pthread_mutex_unlock(&philosopher->meal_mutex);
	philosopher->meals_eaten++;
	usleep(philosopher->table->time_to_eat * 1000);
	put_down_forks(philosopher);
}

void	ph_sleep(t_philosopher *philosopher)
{
	pthread_mutex_lock(&philosopher->state_mutex);
	philosopher->state = 2;
	pthread_mutex_unlock(&philosopher->state_mutex);
	pthread_mutex_lock(&philosopher->table->print_mutex);
	printf("%lld %d is sleeping\n", (current_timestamp() - philosopher->table->start_time), philosopher->id);
	pthread_mutex_unlock(&philosopher->table->print_mutex);
	usleep(philosopher->table->time_to_sleep * 1000);
}
