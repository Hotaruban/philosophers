/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 17:04:09 by jhurpy            #+#    #+#             */
/*   Updated: 2023/10/30 21:59:34 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	*routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	(void)philo;
	pthread_mutex_lock(&philo->table->write_locks);
	printf(GREEN "%d philo\n" NC, philo->id_philo);
	pthread_mutex_unlock(&philo->table->write_locks);
	//while (philo->nb_meals != philo->table->number_of_meals)
	//{
	//	printf(CYAN "%d philo" NC, philo->id_philo);
	//	philo->nb_meals++;
	//}
	return (NULL);
}
