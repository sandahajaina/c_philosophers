/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sranaivo <sranaivo@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 14:57:01 by sranaivo          #+#    #+#             */
/*   Updated: 2024/09/16 17:27:06 by sranaivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int argc, char *argv[])
{
	t_table	table;

	if (check_input(argc, argv))
	{
		init_table(&table, argc, argv);
		create_philosopher_threads(&table);
		cleanup_table(&table);
		return (0);
	}
	printf("Error\n");
	return (1);
}

int	check_input(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	if (argc == 5 || argc == 6)
	{
		while (i < argc)
		{
			j = 0;
			while (argv[i][j])
			{
				if (!((argv[i][j] >= '0') && ((argv[i][j]) <= '9')))
					return (0);
				j++;
			}
			if (ph_atoi(argv[i]) <= 0)
				return (0);
			i++;
		}
		return (1);
	}
	return (0);
}
