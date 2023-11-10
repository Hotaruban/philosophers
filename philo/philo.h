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

typedef enum e_status
{
	_thinking,
	_eating,
	_sleeping,
	_dead,
}	t_status;

typedef struct s_table
{
	unsigned int		nb_philos;
	time_t				time_to_die;
	time_t				time_to_eat;
	time_t				time_to_sleep;
	int					nb_of_meals;
	unsigned int		*set_of_forks;
	t_philo				**philos;
	pthread_mutex_t		write_locks;
	bool				sim_stop;
	time_t				start_time;
}	t_table;

typedef struct s_philo
{
	pthread_t			thread;
	pthread_mutex_t		time_lock;
	pthread_mutex_t		fork_lock;
	t_table				*table;
	int					id;
	int					meals_eaten;
	t_status			status;
	time_t				time_now;
	time_t				time_alive;
}	t_philo;

/*parsing and init functions*/
bool	check_argument(int ac, char **av);
int		init_table(t_table *table, int ac, char **av);

/*write and times functions*/
void	hermes_message(t_philo *ph, char *message);
void	hypnos_touch_philo(t_philo *philo, time_t time_ms);
int		check_if_phylo_alive(t_philo *philo, time_t time_ms);
time_t	get_time(void);

/*routine functions*/
void	*routine(void *data);
void	undertaker(t_table *table);

/*utils functions*/
size_t	ft_strlen(const char *s);
int		ft_atoi(const char *s);
int		ft_isdigit(int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	*ft_calloc(size_t count, size_t size);

/*exit and free functions*/
void	destroy_mutex_table(t_table *table);
void	free_table(t_table *table);
void	destroy_and_free(t_table *table);

#endif
