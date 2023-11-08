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

static int	print_status(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->table->write_locks);
	if (philo->table->sim_stop == true)
	{
		pthread_mutex_unlock(&philo->table->write_locks);
		return (EXIT_FAILURE);
	}
	if (ft_strncmp(str, "All philosopher are full!", 26) == 0)
	{
		printf("%s\n", str);
		philo->table->sim_stop = true;
		pthread_mutex_unlock(&philo->table->write_locks);
		return (EXIT_FAILURE);
	}
	printf("%ld %d %s\n", get_time() - philo->table->start_time,
		philo->id_philo + 1, str);
	if (ft_strncmp(str, "died", 5) == 0)
		philo->table->sim_stop = true;
	pthread_mutex_unlock(&philo->table->write_locks);
	return (EXIT_SUCCESS);
}

int	write_status(t_philo *philo, t_status status)
{
	int	exit_status;

	exit_status = EXIT_SUCCESS;
	if (status == DIED)
		exit_status = print_status(philo, "died");
	else if (status == EAT)
		exit_status = print_status(philo, "is eating");
	else if (status == SLEEP)
		exit_status = print_status(philo, "is sleeping");
	else if (status == THINK)
		exit_status = print_status(philo, "is thinking");
	else if (status == FORK)
		exit_status = print_status(philo, "has taken a fork");
	else if (status == ALL_EAT)
		exit_status = print_status(philo, "All philosopher are full!");
	return (exit_status);
}
