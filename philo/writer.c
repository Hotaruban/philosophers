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

void	print_state_philo(t_philo *philo, time_t *(get_time)(void), char *state)
{
	printf("%ld %d %s\n", (*get_time() - philo->table->start_time), philo->id_philo, state);
}
