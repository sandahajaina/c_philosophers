/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sranaivo <sranaivo@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 14:57:01 by sranaivo          #+#    #+#             */
/*   Updated: 2024/09/08 22:43:09 by sranaivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"

void    start_simulation(t_table *table)
{
    int i;

    i = 0;
    while (i < table->number_philo)
    {
        pthread_join(table->philosophers[i].thread, NULL);
        i++;
    }
}

int main(int argc, char *argv[])
{
    if (argc == 5 || argc == 6)
    {
        t_table table;
        init_table(&table, argc, argv);

        create_philosopher_threads(&table);

        cleanup_table(&table);

        return (0);
    }
    return (1);
}
