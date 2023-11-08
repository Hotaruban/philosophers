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

static bool	kill_philo(t_philo *philo)
{
	time_t	time;

	time = get_time();
	if ((time - philo->last_meal) >= philo->table->time_to_die)
	{
		write_status(philo, DIED);
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
		if (table->nb_of_meals != -1)
			if (table->philos[i]->meals_ate
				< (unsigned int)table->nb_of_meals)
				all_ate_enough = false;
		pthread_mutex_unlock(&table->philos[i]->time_lock);
		i++;
	}
	if (table->nb_of_meals != -1 && all_ate_enough == true)
	{
		write_status(table->philos[0], FORK);
		return (true);
	}
	return (false);
}

void	undertaker(t_table *table)
{
	while (table->sim_stop == false)
	{
		if (end_condition_reached(table) == true)
			return ;
		usleep(100);
	}
	return ;
}
