/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   undertaker.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 23:50:18 by jhurpy            #+#    #+#             */
/*   Updated: 2023/11/02 03:22:39 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

static void	set_sim_stop_flag(t_table *table, bool state)
{
	pthread_mutex_lock(&table->sim_stop_lock);
		table->sim_stop = state;
	pthread_mutex_unlock(&table->sim_stop_lock);
}

bool	has_sim_stopped(t_table *table)
{
	bool	status;

	status = false;
	pthread_mutex_lock(&table->sim_stop_lock);
	if (table->sim_stop == true)
		status = true;
	pthread_mutex_unlock(&table->sim_stop_lock);
	return (status);
}

static bool	kill_philo(t_philo *philo)
{
	time_t	time;

	time = get_time_in_ms();
	if ((time - philo->last_meal) >= philo->table->time_to_die)
	{
		set_sim_stop_flag(philo->table, true);
		write_status(philo, true, DIED);
		pthread_mutex_unlock(&philo->time_lock);
		return (true);
	}
	return (false);
}

static bool	end_condition_reached(t_table *table)
{
	unsigned int	i;
	bool			all_ate_enough;

	all_ate_enough = true;
	i = 0;
	while (i < table->nb_philos)
	{
		pthread_mutex_lock(&table->philos[i]->time_lock);
		if (kill_philo(table->philos[i]))
			return (true);
		if (table->number_of_meals != -1)
			if (table->philos[i]->last_meal
				< (unsigned int)table->number_of_meals)
				all_ate_enough = false;
		pthread_mutex_unlock(&table->philos[i]->time_lock);
		i++;
	}
	if (table->number_of_meals != -1 && all_ate_enough == true)
	{
		set_sim_stop_flag(table, true);
		return (true);
	}
	return (false);
}

void	undertaker(t_table *table)
{
	if (table->number_of_meals == 0)
		return ;
	set_sim_stop_flag(table, false);
	//start with delay
	while (true)
	{
		if (end_condition_reached(table) == true)
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}

