/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 03:43:52 by jhurpy            #+#    #+#             */
/*   Updated: 2023/11/02 01:42:18 by jhurpy           ###   ########.fr       */
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

typedef struct s_philo	t_philo;

typedef struct s_table
{
	unsigned int		nb_philos;
	time_t				time_to_die;
	time_t				time_to_eat;
	time_t				time_to_sleep;
	int					nb_of_meals;
	t_philo				**philos;
	pthread_mutex_t		*fork_locks;
	pthread_mutex_t		write_locks;
	bool				sim_stop;
	time_t				start_time;
}	t_table;

typedef struct s_philo
{
	pthread_t			thread;
	pthread_mutex_t		time_lock;
	t_table				*table;
	int					id_philo;
	unsigned int		meals_ate;
	unsigned int		forks[2];
	time_t				last_meal;
}	t_philo;

typedef enum e_status
{
	DIED = 0,
	EAT = 1,
	SLEEP = 2,
	THINK = 3,
	FORK = 4,
	ALL_EAT = 5,
}	t_status;

bool	check_argument(int ac, char **av);
int 	init_table(t_table *table, int ac, char **av);
void	*routine(void *data);
void	undertaker(t_table *table);
time_t	get_time(void);
void	philo_find_morphee(t_table *table, time_t sleep_time);
int		write_status(t_philo *philo, t_status status);
void	destroy_and_free(t_table *table);
void	free_table(t_table *table);
void	destroy_mutex_table(t_table *table);
size_t	ft_strlen(const char *s);
int		ft_atoi(const char *s);
int		ft_isdigit(int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

#endif
