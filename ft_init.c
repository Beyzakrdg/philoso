/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bekarada <bekarada@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 11:32:53 by bekarada          #+#    #+#             */
/*   Updated: 2025/02/04 18:52:54 by bekarada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_init_philos(t_prog *prog, t_philo *philo,
		pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < prog->nbr_of_philo)
	{
		philo[i].id = i + 1;
		philo[i].left_fork = &forks[i];
		philo[i].right_fork = &forks[(i + 1) % prog->nbr_of_philo];
		philo[i].times_ate = 0;
		philo[i].last_time_ate = ft_get_time();
		philo[i].start_time = ft_get_time();
		philo[i].prog = prog;
		i++;
	}
}

int	ft_init_fork_mutexes(pthread_mutex_t *forks, int nbr_of_philo)
{
	int	i;

	i = 0;
	while (i < nbr_of_philo)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
			return (printf("failed to initialize a mutex"), 1);
		i++;
	}
	return (0);
}

int	ft_init_prog_mutexes(t_prog *prog)
{
	if (pthread_mutex_init(&prog->check_dead, NULL) != 0)
		return (printf("failed to initialize a mutex"), 1);
	if (pthread_mutex_init(&prog->check_last_meal, NULL) != 0)
		return (printf("failed to initialize a mutex"), 1);
	if (pthread_mutex_init(&prog->times_eat, NULL) != 0)
		return (printf("failed to initialize a mutex"), 1);
	if (pthread_mutex_init(&prog->msg_mutex, NULL) != 0)
		return (printf("failed to initialize a mutex"), 1);
	return (0);
}
