/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 03:51:36 by jhurpy            #+#    #+#             */
/*   Updated: 2023/10/30 16:48:02 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

int	ft_atoi(const char *s)
{
	int	i;
	int	sign;
	int	num;

	i = 0;
	sign = 1;
	num = 0;
	while (s[i] == 32 || (s[i] >= 9 && s[i] <= 13))
		i++;
	if (s[i] == 45 || s[i] == 43)
	{
		if (s[i] == 45)
			sign *= -1;
		i++;
	}
	while (s[i] >= 48 && s[i] <= 57)
	{
		num = num * 10 + (s[i] - 48);
		i++;
	}
	return (num * sign);
}

int	ft_isdigit(int c)
{
	return (c >= 48 && c <= 57);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;

	i = 0;
	while ((i < n) && ((s1[i] != '\0') || s2[i] != '\0'))
	{
		if ((unsigned char)s1[i] > (unsigned char)s2[i])
			return (1);
		else if ((unsigned char)s1[i] < (unsigned char)s2[i])
			return (-1); 
		i++;
	}
	return (0);
}

void	*ft_calloc(size_t count, size_t size)
{
	char	*p;
	char	*tmp;
	size_t	n;

	if (count == SIZE_MAX || size == SIZE_MAX)
		return (NULL);
	p = (void *)malloc(count * size);
	if (p == NULL)
		return (NULL);
	n = count * size;
	tmp = p;
	while (n--)
		*(unsigned char *)tmp++ = 0;
	return (p);
}