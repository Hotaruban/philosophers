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

static void	eat_sleep_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->fork_locks[philo->forks[0]]);
	write_status(philo, false, FORK);
	pthread_mutex_lock(&philo->table->fork_locks[philo->forks[1]]);
	write_status(philo, false, FORK);
	write_status(philo, false, EAT);
	pthread_mutex_lock(&philo->time_lock);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->time_lock);
	philo_find_morphee(philo->table, philo->table->time_to_eat);
	if (has_sim_stopped(philo->table) == false)
	{
		pthread_mutex_lock(&philo->time_lock);
		philo->nb_meals += 1;
		pthread_mutex_unlock(&philo->time_lock);
	}
	write_status(philo, false, SLEEP);
	pthread_mutex_unlock(&philo->table->fork_locks[philo->forks[1]]);
	pthread_mutex_unlock(&philo->table->fork_locks[philo->forks[0]]);
	philo_find_morphee(philo->table, philo->table->time_to_sleep);
}

static void	think_routine(t_philo *philo, bool silent)
{
	time_t	time_to_think;

	pthread_mutex_lock(&philo->time_lock);
	time_to_think = (philo->table->time_to_die
			- (get_time() - philo->last_meal)
			- philo->table->time_to_eat) / 2;
	pthread_mutex_unlock(&philo->time_lock);
	if (time_to_think < 0)
		time_to_think = 0;
	if (time_to_think == 0 && silent == true)
		time_to_think = 1;
	if (time_to_think > 600)
		time_to_think = 200;
	if (silent == false)
		write_status(philo, false, THINK);
	philo_find_morphee(philo->table, time_to_think);
}

static void	*lone_philo_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->fork_locks[philo->forks[0]]);
	write_status(philo, false, FORK);
	philo_find_morphee(philo->table, philo->table->time_to_die);
	write_status(philo, false, DIED);
	pthread_mutex_unlock(&philo->table->fork_locks[philo->forks[0]]);
	return (NULL);
}

void	*routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->table->number_of_meals == 0)
		return (NULL);
	pthread_mutex_lock(&philo->time_lock);
	philo->last_meal = philo->table->start_time;
	pthread_mutex_unlock(&philo->time_lock);
	start_delay_diner(philo->table->start_time);
	if (philo->table->time_to_die == 0)
		return (NULL);
	if (philo->table->nb_philos == 1)
		return (lone_philo_routine(philo));
	else if (philo->id_philo % 2)
		think_routine(philo, true);
	while (has_sim_stopped(philo->table) == false)
	{
		eat_sleep_routine(philo);
		think_routine(philo, false);
	}
	return (NULL);
}
