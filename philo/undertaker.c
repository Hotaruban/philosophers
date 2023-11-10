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

static void	thanatos_take_philo(t_table *table, unsigned int i)
{
	pthread_mutex_lock(&table->write_locks);
	printf(RED"%ld %d died\n"NC, get_time()
		- table->start_time, table->philos[i]->id + 1);
	i = -1;
	while (++i < table->nb_philos)
		table->philos[i]->status = _dead;
	return ;
}

static void	everyone_eaten(t_table *table)
{
	unsigned int	i;

	i = -1;
	table->sim_stop = true;
	while (++i < table->nb_philos)
		table->philos[i]->status = _dead;
	usleep(15000);
	printf(RED"All Philosophers has eaten %d time(s), they are full.\n"NC,
		table->nb_of_meals);
	return ;
}

void	undertaker(t_table *table)
{
	unsigned int	i;
	unsigned int	nbr;

	while (1)
	{
		i = -1;
		nbr = 0;
		usleep(1);
		while (++i < table->nb_philos && nbr < table->nb_philos)
		{
			if (table->philos[i]->status == _dead || table->sim_stop == true)
				return (thanatos_take_philo(table, i));
			if (table->nb_of_meals != -1)
			{
				if (table->philos[i]->meals_eaten >= table->nb_of_meals)
				nbr = nbr + 1;
			}
		}
		if (table->nb_of_meals != -1 && nbr == table->nb_philos)
			return (everyone_eaten(table));
	}
}
