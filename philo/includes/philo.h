/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sranaivo <sranaivo@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 15:04:05 by sranaivo          #+#    #+#             */
/*   Updated: 2024/09/16 17:10:13 by sranaivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

typedef struct s_fork t_fork;
typedef struct s_table t_table;

struct s_fork
{
    int             id;
    pthread_mutex_t mutex;
};

typedef struct s_philosopher {
    int             id;
    pthread_t       thread;
    int             left_fork;
    int             right_fork;
    pthread_mutex_t m_last_meal_time;
    long long       last_meal_time;
    long long       start_time;
    pthread_mutex_t m_start_time;
    pthread_mutex_t m_meals_eaten;
    int             meals_eaten;
    t_table         *table;
} t_philosopher;

struct  s_table
{
    int             number_philo;
    int             time_to_die;
    int             time_to_eat;
    int             time_to_sleep;
    int             number_meals_required;
    long long       start_time;
    pthread_mutex_t print_mutex;
    t_fork          forks[200];
    t_philosopher   philosophers[200];
    pthread_mutex_t simulation_mutex;
    int             simulation_running;
};

void    init_table(t_table *table, int argc, char **argv);
void	*philosopher_routine(void *arg);
void	init_philosophers(t_table *table);
void    create_philosopher_threads(t_table *table);
int     ph_atoi(const char *nptr);
long long   current_timestamp(void);
void    cleanup_table(t_table *table);
int	    take_forks(t_philosopher *philosopher);
void	think(t_philosopher *philosopher);
void	put_down_forks(t_philosopher *philosopher);
void	eat(t_philosopher *philosopher);
void	ph_sleep(t_philosopher *philosopher);
void    *monitoring_routine(void *arg);
void    print_status(t_philosopher *philosopher, char *message);
void	ph_usleep(t_philosopher *philosopher ,int sleep_time);
void	init_fork(t_table *table);
int	    check_simulation_running(t_philosopher *philosopher);
int     check_input(int argc, char **argv);
void	take_right_fork(t_philosopher *philosopher);
void	take_left_fork(t_philosopher *philosopher);

#endif

