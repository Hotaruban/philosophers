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

void	*routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	(void)philo;
	pthread_mutex_lock(&philo->time_lock);
	philo->last_meal = philo->table->start_time;
	pthread_mutex_unlock(&philo->time_lock);
	if (philo->table->time_to_die == 0 || philo->table->number_of_meals == 0)
		return (NULL);
	if (philo->table->nb_philos == 1)
		// routine_one_philo(philo);
	else if (philo->id_philo % 2 == 0)
		//think_routine(philo);
	while (philo->table->alive == true)
	{
		// eat_sleep_think_routine(philo);
	}
	//pthread_mutex_lock(&philo->table->write_locks);
	//printf(GREEN "%d philo\n" NC, philo->id_philo);
	//pthread_mutex_unlock(&philo->table->write_locks);
	//while (philo->nb_meals != philo->table->number_of_meals)
	//{
	//	printf(CYAN "%d philo" NC, philo->id_philo);
	//	philo->nb_meals++;
	//}
	return (NULL);
}
