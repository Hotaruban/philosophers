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

static int	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork_lock);
	if (philo->table->set_of_forks[philo->id_philo] == 1 
		&& philo->table->set_of_forks[(philo->id_philo + 1)
			% philo->table->nb_philos] == 1)
	{
		pthread_mutex_unlock(&philo->fork_lock);
		philo->status = _thinking;
		return (1);
	}
	if (philo->table->set_of_forks[philo->id_philo] == 0)
	{
		philo->table->set_of_forks[philo->id_philo] = 1;
		hermes_message(philo, "take fork [0]");
	}
	if (philo->table->set_of_forks[(philo->id_philo + 1)
			% philo->table->nb_philos] == 0)
	{
		philo->table->set_of_forks[(philo->id_philo + 1)
			% philo->table->nb_philos] = 1;
		hermes_message(philo, "take fork [1]");
		philo->status = _eating;
		if (philo->table->nb_of_meals != -1)
			philo->meals_eaten++;
		pthread_mutex_unlock(&philo->fork_lock);
		return (0);
	}
	pthread_mutex_unlock(&philo->fork_lock);
	return (1);
}

static void	put_forks_down(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork_lock);
	philo->table->set_of_forks[philo->id_philo] = 0;
	philo->table->set_of_forks[(philo->id_philo + 1)
			% philo->table->nb_philos] = 0;
	philo->status = _thinking;
	pthread_mutex_unlock(&philo->fork_lock);
}

static void	daily_routine(t_philo *philo)
{
	while (philo->status != _dead)
	{
		if (philo->status == _thinking)
		{
			hermes_message(philo, "is thinking");
			while (philo->status == _thinking)
				if (take_forks(philo))
					hypnos_touch_philo(philo, 0);
		}
		else if (philo->status == _eating)
		{
			hermes_message(philo, "is eating");
			philo->time_alive = philo->time_now + philo->table->time_to_die;
			philo->status = _sleeping;
			hypnos_touch_philo(philo, philo->table->time_to_eat);
		}
		else if (philo->status == _sleeping)
		{
			hermes_message(philo, "is sleeping");
			put_forks_down(philo);
			hypnos_touch_philo(philo, philo->table->time_to_sleep);
		}
	}
}

void	*routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	philo->time_now = get_time();
	philo->time_alive = philo->table->start_time + philo->table->time_to_die;
	if (philo->id_philo % 2 == 0 && philo->table->set_of_forks[philo->id_philo] == 0)
		take_forks(philo);
	else
	{
		philo->status = _thinking;
		usleep(4999);
	}
	daily_routine(philo);
	return (NULL);
}
