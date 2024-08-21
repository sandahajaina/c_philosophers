/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sranaivo <sranaivo@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 14:57:01 by sranaivo          #+#    #+#             */
/*   Updated: 2024/08/21 15:03:56 by sranaivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"

void *hello_world(void *arg) {
    (void) arg;
    printf("Hello from thread %ld!\n", pthread_self());
    return NULL;
}

int main(int argc, char *argv[])
{
    // (void) argv;
    // (void) argc;
    // pthread_t   thread1, thread2;

    // pthread_create(&thread1, NULL, hello_world, NULL);
    // pthread_create(&thread2, NULL, hello_world, NULL);

    // pthread_join(thread1, NULL);
    //pthread_join(thread2, NULL);

    if (argc == 5 || argc == 6)
    {
        t_table table;
        init_table(&table, argc, argv);

        

        //printf("philos: %d\ntime_to_die: %d\ntime_to_eat: %d\ntime_to_sleep: %d\n", 
        //table.number_philo, table.time_to_die, table.time_to_eat, table.time_to_sleep);
        return (0);
    }
    return (1);
}
