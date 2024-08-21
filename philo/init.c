/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sranaivo <sranaivo@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 13:55:34 by sranaivo          #+#    #+#             */
/*   Updated: 2024/08/21 16:31:48 by sranaivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    init_table(t_table *table, int argc, char **argv)
{
    int i;
    
    table->number_philo = ph_atoi(argv[1]);
    table->time_to_die = ph_atoi(argv[2]);
    table->time_to_eat = ph_atoi(argv[3]);
    table->time_to_sleep = ph_atoi(argv[4]);
    if (argc == 6)
        table->number_meals_required = ph_atoi(argv[5]);
    table->forks = malloc(sizeof(pthread_mutex_t) * table->number_philo);
    table->philosophers = malloc(sizeof(t_philosopher) * table->number_philo);

    i = -1;
    while (++i < table->number_philo)
        pthread_mutex_init(&table->forks[i], NULL);
    pthread_mutex_init(&table->print_mutex, NULL);
    i = -1;
    while (++i < table->number_philo)
    {
        table->philosophers[i].id = i + 1;
        
    }
}
