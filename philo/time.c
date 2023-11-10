/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 14:29:54 by jhurpy            #+#    #+#             */
/*   Updated: 2023/10/30 16:54:06 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

time_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	check_if_phylo_alive(t_philo *philo, time_t time)
{
	pthread_mutex_lock(&philo->time_lock);
	if (time > philo->time_alive)
	{
		philo->status = _dead;
		pthread_mutex_unlock(&philo->time_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->time_lock);
	return (0);
}

void	hypnos_touch_philo(t_philo *philo, time_t time_ms)
{
	time_t	time;

	while (philo->status != _dead)
	{
		usleep(1);
		time = get_time();
		if (check_if_phylo_alive(philo, time)
			|| time - philo->time_now >= time_ms)
			break ;
	}
}
