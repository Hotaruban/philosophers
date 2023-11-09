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

void	hermes_message(t_philo *ph, char *message)
{
	pthread_mutex_lock(&ph->table->write_locks);
	ph->time_now = get_time();
	printf("%ld %d %s\n", ph->time_now - ph->table->start_time,
		ph->id_philo + 1, message);
	pthread_mutex_unlock(&ph->table->write_locks);
}
