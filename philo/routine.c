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

static int	take_forks(t_philo *ph)
{
	pthread_mutex_lock(&ph->fork_lock);
	if (ph->table->set_of_forks[ph->id] == 1
		&& ph->table->set_of_forks[(ph->id + 1) % ph->table->nb_philos] == 1)
	{
		pthread_mutex_unlock(&ph->fork_lock);
		ph->status = _thinking;
		return (1);
	}
	if (ph->table->set_of_forks[ph->id] == 0)
	{
		ph->table->set_of_forks[ph->id] = 1;
		hermes_message(ph, "take fork");
	}
	if (ph->table->set_of_forks[(ph->id + 1) % ph->table->nb_philos] == 0)
	{
		ph->table->set_of_forks[(ph->id + 1) % ph->table->nb_philos] = 1;
		hermes_message(ph, "take fork");
		ph->status = _eating;
		if (ph->table->nb_of_meals != -1)
			ph->meals_eaten++;
		pthread_mutex_unlock(&ph->fork_lock);
		return (0);
	}
	pthread_mutex_unlock(&ph->fork_lock);
	return (1);
}

static void	put_forks_down(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork_lock);
	philo->table->set_of_forks[philo->id] = 0;
	philo->table->set_of_forks[(philo->id + 1)
		% philo->table->nb_philos] = 0;
	if (philo->status != _dead)
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
			if (philo->status != _dead)
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
	philo->status = _thinking;
	philo->time_now = get_time();
	if (philo->table->nb_of_meals == 0)
		return (NULL);
	philo->time_alive = philo->table->start_time + philo->table->time_to_die;
	if (philo->id % 2 == 0 && philo->table->set_of_forks[philo->id] == 0)
		take_forks(philo);
	else
	{
		philo->status = _thinking;
		usleep(4999);
	}
	daily_routine(philo);
	return (NULL);
}
