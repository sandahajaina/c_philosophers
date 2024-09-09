/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sranaivo <sranaivo@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 15:04:05 by sranaivo          #+#    #+#             */
/*   Updated: 2024/09/09 16:31:20 by sranaivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

typedef struct s_table t_table;
typedef struct s_fork  t_fork;
typedef enum e_state    t_state;

typedef struct s_philosopher {
    int             id;
    pthread_t       thread;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    pthread_mutex_t state_mutex;
    int             state;
    pthread_mutex_t meal_mutex;
    long long       last_meal_time;
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
    long long            start_time;
    pthread_mutex_t print_mutex;
    pthread_mutex_t *forks;
    t_philosopher   *philosophers;
    pthread_mutex_t simulation_mutex;
    int             simulation_running;
};

struct  s_fork
{
    int             fork_id;
    pthread_mutex_t *fork;
};

enum    e_state
{
    SLEEPING,
    EATING,
    THINKING,
    DEAD
};

void    init_table(t_table *table, int argc, char **argv);
void    create_philosopher_threads(t_table *table);
int     ph_atoi(const char *nptr);
long long   current_timestamp(void);
void    cleanup_table(t_table *table);
int     has_died(t_philosopher *philosopher);
void	take_forks(t_philosopher *philosopher);
void	think(t_philosopher *philosopher);
void	put_down_forks(t_philosopher *philosopher);
void	eat(t_philosopher *philosopher);
void	ph_sleep(t_philosopher *philosopher);
void    *monitoring_routine(void *arg);

#endif

