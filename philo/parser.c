/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 03:45:13 by jhurpy            #+#    #+#             */
/*   Updated: 2023/10/30 21:05:57 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

static bool	is_number(char *number)
{
	int	i;

	i = 0;
	if (ft_strlen(number) == 0)
	{
		printf(RED "Error: argument %d is empty\n" NC, i);
		return (false);
	}
	while (number[i])
	{
		if (ft_isdigit(number[i]) == false)
			return (false);
		i++;
	}
	return (true);
}

static bool	is_integer(char *integer, int flag)
{
	int num;

	if (ft_strlen(integer) > 10)
	{
		printf(RED "Error: argument %d is too long\n" NC, flag);
		return (false);
	}
	num = ft_atoi(integer);
	if (num > INT_MAX || num < 0)
	{
		printf(RED "Error: argument %d is not a valid argument\n" NC, flag);
		return (false);
	}
	if (flag == 1 && (num <= 0 || num > MAX_PHILO))
	{
		printf(RED "Error: number of philosophers incorrect\n" NC);
		return (false);
	}
	return (true);
}

bool	check_argument(int ac, char **av)
{
	int i;

	i = 1;
	while (i < ac)
	{
		if (is_number(av[i]) == false)
		{
			printf(RED "Error: argument %d is not a number\n" NC, i);
			return (false);
		}
		if (is_integer(av[i], i) == false)
			return (false);
		i++;
	}
	return (true);
}
