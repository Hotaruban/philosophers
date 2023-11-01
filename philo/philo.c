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

	table->start_time = get_time() + (table->nb_philos * 2 * 10);
	i = 0;
	while (i < table->nb_philos)
	{
		if (pthread_create(&table->philos[i]->thread, NULL, &routine,
				table->philos[i]) != 0)
		{
			printf(RED "Error: thread creation failed\n" NC);
			return (false);
		}
		i++;
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
	destroy_mutex_table(table);
	free_table(table);
}

int	main(int ac, char **av)
{
	t_table	*table;

	table = NULL;
	if (ac < 5 || ac > 6)
	{
		printf(RED "Error: wrong number of arguments\n" NC);
		return (EXIT_FAILURE);
	}
	if (check_argument(ac, av) == false)
		return (EXIT_FAILURE);
	table = init_table(ac, av, 1);
	if (!table)
		return (EXIT_FAILURE);
	if (start_simulation(table) == false)
		return (EXIT_FAILURE);
	if (table->nb_philos > 1)
		// undertaker(table); check if a philo is dead
	stop_simulation(table);
	return (EXIT_SUCCESS);
}
