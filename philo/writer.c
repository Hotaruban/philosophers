/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   writer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 03:43:45 by jhurpy            #+#    #+#             */
/*   Updated: 2023/10/30 20:25:56 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

static void	print_status(t_philo *philo, char *str)
{
	printf("%ld %d %s\n", get_time() - philo->table->start_time,
		philo->id_philo + 1, str);
}

void	write_status(t_philo *philo, bool reaper_report, t_status status)
{
	pthread_mutex_lock(&philo->table->write_locks);
	// usleep(100);
	if (has_sim_stopped(philo->table) == true && reaper_report == false)
	{
		pthread_mutex_unlock(&philo->table->write_locks);
		return ;
	}
	if (status == DIED)
		print_status(philo, "died");
	else if (status == EAT && (philo->nb_meals < (unsigned int)philo->table-> \
	number_of_meals || philo->table->number_of_meals == -1))
		print_status(philo, "is eating");
	else if (status == SLEEP)
		print_status(philo, "is sleeping");
	else if (status == THINK)
		print_status(philo, "is thinking");
	else if (status == FORK)
		print_status(philo, "has taken a fork");
	pthread_mutex_unlock(&philo->table->write_locks);
}
