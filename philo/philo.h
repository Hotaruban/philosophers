/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 03:43:52 by jhurpy            #+#    #+#             */
/*   Updated: 2023/10/31 01:17:11 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdbool.h>
# include <limits.h>

# define NC		"\e[0m"
# define RED	"\e[31m"
# define GREEN	"\e[32m"
# define PURPLE	"\e[35m"
# define CYAN	"\e[36m"

# define MAX_PHILO		250

# define FORK			"has taken a fork"
# define EAT			"is eating"
# define SLEEP			"is sleeping"
# define THINK			"is thinking"
# define DIED			"died"

typedef struct s_philo	t_philo;

typedef struct s_table
{
	unsigned int		nb_philos;
	time_t				time_to_die;
	time_t				time_to_eat;
	time_t				time_to_sleep;
	unsigned int		number_of_meals;
	time_t				start_time;
	pthread_mutex_t		write_locks;
	pthread_mutex_t		*fork_locks;
	t_philo				**philos;
}	t_table;

typedef struct s_philo
{
	pthread_t			thread;
	int					id_philo;
	time_t				last_meal;
	unsigned int		nb_meals;
	unsigned int		forks[2];
	pthread_mutex_t		time_lock;
	t_table				*table;
}	t_philo;

t_table	*init_table(int ac, char **av, int index);
void	destroy_mutex_table(t_table *table);

bool	check_argument(int ac, char **av);

void	*routine(void *data);

time_t	get_time(void);
void	start_delay_diner(time_t start_time);

void	print_state_philo(t_philo *philo, time_t *(get_time)(void), char *state);

size_t	ft_strlen(const char *s);
int		ft_atoi(const char *s);
int		ft_isdigit(int c);

#endif
