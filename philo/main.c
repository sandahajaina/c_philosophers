/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sranaivo <sranaivo@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 14:57:01 by sranaivo          #+#    #+#             */
/*   Updated: 2024/09/16 11:42:03 by sranaivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_meals_eaten(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->number_philo)
	{
		printf("%d : %d\n", table->philosophers[i].id,
			table->philosophers[i].meals_eaten);
		i++;
	}
}

int	main(int argc, char *argv[])
{
	t_table	table;

	if (argc == 5 || argc == 6)
	{
		init_table(&table, argc, argv);
		create_philosopher_threads(&table);
		print_meals_eaten(&table);
		cleanup_table(&table);
		return (0);
	}
	return (1);
}
