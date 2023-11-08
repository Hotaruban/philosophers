/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 03:43:55 by jhurpy            #+#    #+#             */
/*   Updated: 2023/10/31 23:02:58 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

static bool	start_simulation(t_table *table)
{
	unsigned int	i;

	table->start_time = get_time();
	i = 0;
	while (i < table->nb_philos)
	{
		if (pthread_create(&table->philos[i]->thread, NULL, &routine,
				table->philos[i]) != 0)
		{
			destroy_and_free(table);
			return (printf(RED "Error: thread creation failed\n" NC), false);
		}
		usleep(7);
		i += 2;
		if (i >= table->nb_philos && i % 2 == 0)
			i = 1;
	}
	return (true);
}

static void	stop_simulation(t_table *table)
{
	unsigned int	i;

	i = 0;
	while (i < table->nb_philos)
	{
		pthread_join(table->philos[i]->thread, NULL);
		i++;
	}
	destroy_and_free(table);
}

int	main(int ac, char **av)
{
	t_table	table;

	if (ac < 5 || ac > 6)
		return (printf(RED "Error: wrong number of arguments\n" NC),
			EXIT_FAILURE);
	if (check_argument(ac, av) == false)
		return (EXIT_FAILURE);
	if (init_table(&table, ac, av) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (start_simulation(&table) == false)
		return (EXIT_FAILURE);
	undertaker(&table);
	stop_simulation(&table);
	return (EXIT_SUCCESS);
}
