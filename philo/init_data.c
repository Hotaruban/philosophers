/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 14:50:43 by jhurpy            #+#    #+#             */
/*   Updated: 2023/10/30 21:39:36 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

static pthread_mutex_t	*init_forks(t_table *table)
{
	pthread_mutex_t	*forks;
	unsigned int	i;

	forks = malloc(sizeof(pthread_mutex_t) * table->nb_philos);
	if (!forks)
	{
		printf(RED "Error: malloc failed\n" NC);
		return (0);
	}
	i = 0;
	while (i < table->nb_philos)
	{
		if (pthread_mutex_init(&forks[i], NULL) == -1)
		{
			printf(RED "Error: mutex init failed\n" NC);
			return (0);
		}
		i++;
	}
	return (forks);
}

static void	assign_forks(t_philo *philo)
{
	if (philo->id_philo % 2 == 0)
	{
		philo->forks[0] = philo->id_philo;
		philo->forks[1] = (philo->id_philo + 1) % philo->table->nb_philos;
	}
	else
	{
		philo->forks[0] = (philo->id_philo + 1) % philo->table->nb_philos;
		philo->forks[1] = philo->id_philo;
	}
}

static bool	init_mutex_table(t_table *table)
{
	table->fork_locks = init_forks(table);
	if (!table->fork_locks)
		return (false);
	if (pthread_mutex_init(&table->write_locks, NULL) == -1)
	{
		printf(RED "Error: mutex init failed\n" NC);
		return (false);
	}
	return (true);
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
		philos[i]->table = table;
		philos[i]->id_philo = i;
		philos[i]->nb_meals = 0;
		assign_forks(philos[i]);
		i++;
	}
	return (philos);
}

t_table	*init_table(int ac, char **av, int index)
{
	t_table	*table;

	table = malloc(sizeof(t_table));
	if (!table)
		return (NULL);
	table->nb_philos = ft_atoi(av[index++]);
	table->time_to_die = ft_atoi(av[index++]);
	table->time_to_eat = ft_atoi(av[index++]);
	table->time_to_sleep = ft_atoi(av[index++]);
	table->number_of_meals = -1;
	if (ac == 6)
		table->number_of_meals = ft_atoi(av[index++]);
	if (init_mutex_table(table) == false)
		return (NULL);
	table->philos = init_philosophers(table);
	return (table);
}
