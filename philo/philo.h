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
	int					number_of_meals;
	t_philo				**philos;
	pthread_mutex_t		*fork_locks;
	pthread_mutex_t		sim_stop_lock;
	pthread_mutex_t		write_locks;
	bool				sim_stop;
	time_t				start_time;
	pthread_t			undertaker;
}	t_table;

typedef struct s_philo
{
	pthread_t			thread;
	pthread_mutex_t		time_lock;
	t_table				*table;
	int					id_philo;
	unsigned int		nb_meals;
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
}	t_status;

bool	check_argument(int ac, char **av);
t_table	*init_table(int ac, char **av, int index);
void	*routine(void *data);
void	*undertaker(void *data);
bool	has_sim_stopped(t_table *table);
time_t	get_time(void);
void	philo_find_morphee(t_table *table, time_t sleep_time);
void	start_delay_diner(time_t start_time);
void	write_status(t_philo *philo, bool reaper_report, t_status status);
void	destroy_and_free(t_table *table);
void	free_table(t_table *table);
void	destroy_mutex_table(t_table *table);
size_t	ft_strlen(const char *s);
int		ft_atoi(const char *s);
int		ft_isdigit(int c);

#endif
