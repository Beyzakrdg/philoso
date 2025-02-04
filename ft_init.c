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

int	ft_init_monitor_mutexes(t_monitor *monitor)
{
	if (pthread_mutex_init(&monitor->check_dead, NULL) != 0)
		return (ft_putstr_fd("failed to initialize a mutex", 2), 1);
	if (pthread_mutex_init(&monitor->check_last_meal, NULL) != 0)
		return (ft_putstr_fd("failed to initialize a mutex", 2), 1);
	if (pthread_mutex_init(&monitor->times_eat, NULL) != 0)
		return (ft_putstr_fd("failed to initialize a mutex", 2), 1);
	if (pthread_mutex_init(&monitor->message_mutex, NULL) != 0)
		return (ft_putstr_fd("failed to initialize a mutex", 2), 1);
	return (0);
}

void	ft_init_philos(t_monitor *monitor, t_philo *philo,
		pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < monitor->nbr_of_philo)
	{
		philo[i].id_philo = i + 1;
		philo[i].fork_l = &forks[i];
		philo[i].fork_r = &forks[(i + 1) % monitor->nbr_of_philo];
		philo[i].times_ate = 0;
		philo[i].last_time_ate = ft_set_time();
		philo[i].start_time = ft_set_time();
		philo[i].monitor = monitor;
		i++;
	}
}

int	ft_init_mutexes(pthread_mutex_t	*forks, int nbr_of_philo)
{
	int	i;

	i = 0;
	while (i < nbr_of_philo)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
			return (ft_putstr_fd("failed to initialize a mutex", 2), 1);
		i++;
	}
	return (0);
}
