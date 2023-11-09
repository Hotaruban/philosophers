/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 14:50:43 by jhurpy            #+#    #+#             */
/*   Updated: 2023/10/31 01:18:53 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

static int	init_mutex_philo(t_philo *philo)
{
	if (pthread_mutex_init(&philo->time_lock, 0) == -1)
		return (printf(RED "Error: mutex init failed\n" NC), EXIT_FAILURE);
	if (pthread_mutex_init(&philo->fork_lock, 0) == -1)
		return (printf(RED "Error: mutex init failed\n" NC), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static t_philo	**init_philosophers(t_table *table)
{
	t_philo			**philo;
	unsigned int	i;

	philo = malloc(sizeof(t_philo) * table->nb_philos);
	if (!philo)
		return (printf(RED "Error: malloc failed\n" NC), NULL);
	i = 0;
	while (i < table->nb_philos)
	{
		philo[i] = malloc(sizeof(t_philo) * 1);
		if (!philo[i])
			return (printf(RED "Error: malloc failed\n" NC), NULL);
		if (init_mutex_philo(philo[i]) == EXIT_FAILURE)
			return (NULL);
		philo[i]->table = table;
		philo[i]->id_philo = i;
		philo[i]->meals_eaten = 0;
		philo[i]->time_now = 0;
		philo[i]->time_alive = 0;
		i++;
	}
	return (philo);
}

int init_table(t_table* table, int ac, char **av)
{
	table->nb_philos = ft_atoi(av[1]);
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
	table->nb_of_meals = -1;
	if (ac == 6)
		table->nb_of_meals = ft_atoi(av[5]);
	table->set_of_forks = ft_calloc(table->nb_philos, sizeof(size_t));
	table->philos = init_philosophers(table);
	if (!table->philos)
		return (EXIT_FAILURE);
	if (pthread_mutex_init(&table->write_locks, NULL) == -1)
		return (printf(RED "Error: mutex init failed\n" NC), EXIT_FAILURE);
	table->sim_stop = false;
	table->start_time = 0;
	return (EXIT_SUCCESS);
}
