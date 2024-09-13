/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sranaivo <sranaivo@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 14:57:01 by sranaivo          #+#    #+#             */
/*   Updated: 2024/09/13 16:57:30 by sranaivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
		t_table table;

	if (argc == 5 || argc == 6)
	{
		init_table(&table, argc, argv);
		create_philosopher_threads(&table);
		cleanup_table(&table);
		return (0);
	}
	return (1);
}
