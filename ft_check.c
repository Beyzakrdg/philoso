/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bekarada <bekarada@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 11:32:53 by bekarada          #+#    #+#             */
/*   Updated: 2025/02/04 18:42:27 by bekarada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_stop_simulation(t_monitor *monitor)
{
	int	res;

	pthread_mutex_lock(&monitor->check_dead);
	res = monitor->stop_simulation;
	pthread_mutex_unlock(&monitor->check_dead);
	return (res);
}

size_t	ft_check_last_time_ate(t_philo *philo)
{
	size_t	res;

	pthread_mutex_lock(&philo->monitor->check_last_meal);
	res = philo->last_time_ate;
	pthread_mutex_unlock(&philo->monitor->check_last_meal);
	return (res);
}

int	ft_check_times_ate(t_philo *philo)
{
	int	res;

	pthread_mutex_lock(&philo->monitor->times_eat);
	res = philo->times_ate;
	pthread_mutex_unlock(&philo->monitor->times_eat);
	return (res);
}
