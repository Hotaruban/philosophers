/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 17:04:09 by jhurpy            #+#    #+#             */
/*   Updated: 2023/10/31 02:29:48 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

static int	eating(t_philo *philo)
{
	if (write_status(philo, FORK) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (write_status(philo, FORK) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (write_status(philo, EAT) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	pthread_mutex_lock(&philo->time_lock);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->time_lock);
	philo_find_morphee(philo->table, philo->table->time_to_eat);
	if (philo->table->sim_stop == false)
	{
		pthread_mutex_lock(&philo->time_lock);
		philo->meals_ate += 1;
		pthread_mutex_unlock(&philo->time_lock);
	}
	return (EXIT_SUCCESS);
}

static int	eat_sleep_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->fork_locks[philo->forks[0]]);
	pthread_mutex_lock(&philo->table->fork_locks[philo->forks[1]]);
	if (eating(philo) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	write_status(philo, SLEEP);
	pthread_mutex_unlock(&philo->table->fork_locks[philo->forks[1]]);
	pthread_mutex_unlock(&philo->table->fork_locks[philo->forks[0]]);
	philo_find_morphee(philo->table, philo->table->time_to_sleep);
	write_status(philo, THINK);
	return (EXIT_SUCCESS);
}

static void	*lone_philo_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->fork_locks[philo->forks[0]]);
	write_status(philo, FORK);
	philo_find_morphee(philo->table, philo->table->time_to_die);
	write_status(philo, DIED);
	pthread_mutex_unlock(&philo->table->fork_locks[philo->forks[0]]);
	return (NULL);
}

void	*routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->table->nb_of_meals == 0)
		return (NULL);
	philo->last_meal = philo->table->start_time;
	if (philo->table->time_to_die == 0)
		return (NULL);
	if (philo->table->nb_philos == 1)
		return (lone_philo_routine(philo));
	while (philo->table->sim_stop == false)
		eat_sleep_routine(philo);
	return (NULL);
}
