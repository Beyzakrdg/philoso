/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bekarada <bekarada@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 17:30:41 by bekarada          #+#    #+#             */
/*   Updated: 2025/02/03 18:31:59 by bekarada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdbool.h>

typedef struct s_table	t_table;

typedef struct s_philo
{
	pthread_t			thread;
	int					id;
	int					eat_meal;
	int					eaten_meal;
	size_t				last_meal;
	size_t				time_to_die;
	size_t				time_to_eat;
	size_t				time_to_sleep;
	int					nbr_of_philo;
	int					count_eat;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*write_mutex;
	pthread_mutex_t		*meal_mutex;
	t_table				*table;	
}	t_philo;

typedef struct s_table
{
	int				num_philos;
	pthread_mutex_t	meals_mutex;
	size_t			time_begin;
	pthread_mutex_t	table_mutex;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	*forks;
	pthread_t		monitor;
	bool			ready_philos;
	bool			ready_monitor;
	bool			completed_philos;
	t_philo			*philo;
}	t_table;

void	handle_error(char *str);

void	ft_init(t_table **table, int philo_number);

void	*ft_monitor(void *philo_void);

void	eating(t_philo *philo);
void	sleeping(t_philo *philo);
void	taking(t_philo *philo, pthread_mutex_t *fork);

bool	ft_is_done(t_table *table);
void	*ft_routine_philo(void *philo);

int		ft_destroy(t_table *table, char *str);
int		ft_create_threads(t_table *table);

size_t	get_time(void);

long	ft_atoi(const char *str);
int		ft_isnum(char *str);
int		ft_strlen(char *str);
void	ft_usleep(size_t mls);
void	write_msg(t_philo *philo, char *str);

#endif