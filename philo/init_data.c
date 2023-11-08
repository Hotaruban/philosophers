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

static pthread_mutex_t	*init_forks(t_table *table)
{
	pthread_mutex_t	*forks;
	unsigned int	i;

	forks = malloc(sizeof(pthread_mutex_t) * table->nb_philos);
	if (!forks)
		return (printf(RED "Error: malloc failed\n" NC), NULL);
	i = 0;
	while (i < table->nb_philos)
	{
		if (pthread_mutex_init(&forks[i], NULL) == -1)
			return (printf(RED "Error: mutex init failed\n" NC), NULL);
		i++;
	}
	return (forks);
}

static t_philo	**init_philosophers(t_table *table)
{
	t_philo			**philos;
	unsigned int	i;

	philos = malloc(sizeof(t_philo) * table->nb_philos);
	if (!philos)
		return (printf(RED "Error: malloc failed\n" NC), NULL);
	i = 0;
	while (i < table->nb_philos)
	{
		philos[i] = malloc(sizeof(t_philo) * 1);
		if (!philos[i])
			return (printf(RED "Error: malloc failed\n" NC), NULL);
		if (pthread_mutex_init(&philos[i]->time_lock, 0) == -1)
			return (printf(RED "Error: mutex init failed\n" NC), NULL);
		philos[i]->table = table;
		philos[i]->id_philo = i;
		philos[i]->meals_ate = 0;
		philos[i]->forks[0] = philos[i]->id_philo;
		philos[i]->forks[1] = (philos[i]->id_philo + 1) % philos[i]->table->nb_philos;
		philos[i]->last_meal = 0;
		i++;
	}
	return (philos);
}

static bool	init_mutex_table(t_table *table)
{
	table->fork_locks = init_forks(table);
	if (!table->fork_locks)
		return (false);
	if (pthread_mutex_init(&table->write_locks, NULL) == -1)
		return (printf(RED "Error: mutex init failed\n" NC), false);
	return (true);
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
	table->philos = init_philosophers(table);
	if (!table->philos)
		return (EXIT_FAILURE);
	if (init_mutex_table(table) == false)
		return (EXIT_FAILURE);
	table->sim_stop = false;
	table->start_time = 0;
	return (EXIT_SUCCESS);
}
