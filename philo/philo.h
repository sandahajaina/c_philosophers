/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sranaivo <sranaivo@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 15:04:05 by sranaivo          #+#    #+#             */
/*   Updated: 2024/08/21 15:09:47 by sranaivo         ###   ########.fr       */
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

typedef struct s_philosopher {
    int             id;
    pthread_t       thread;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    pthread_mutex_t state_mutex;
    int             state;
    long            last_meal_time;
    int             meals_eaten;
} t_philosopher;

struct  s_table
{
    int             number_philo;
    int             time_to_die;
    int             time_to_eat;
    int             time_to_sleep;
    int             number_meals_required;
    pthread_mutex_t print_mutex;
    pthread_mutex_t *forks;
    t_philosopher   *philosophers;
};

void    init_table(t_table *table, int argc, char **argv);
int     ph_atoi(const char *nptr);
long    current_timestamp(void);

#endif

