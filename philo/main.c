/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sranaivo <sranaivo@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 14:57:01 by sranaivo          #+#    #+#             */
/*   Updated: 2024/08/17 14:52:29 by sranaivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"

int main(int argc, char *argv[])
{
    (void) argv;
    t_rules rules;
    if (argc == 5 || argc == 6)
    {
        printf("philo");
        return (0);
    }
    return (1);
}
