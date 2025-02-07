/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bekarada <bekarada@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 11:32:53 by bekarada          #+#    #+#             */
/*   Updated: 2025/02/04 18:42:27 by bekarada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_check_last_time_ate(t_philo *philo)
{
	size_t	res;

	pthread_mutex_lock(&philo->prog->check_last_meal);
	res = philo->last_time_ate;
	pthread_mutex_unlock(&philo->prog->check_last_meal);
	return (res);
}

int	ft_check_times_ate(t_philo *philo)
{
	int	res;

	pthread_mutex_lock(&philo->prog->times_eat);
	res = philo->times_ate;
	pthread_mutex_unlock(&philo->prog->times_eat);
	return (res);
}

int	ft_stop_simulation(t_prog *prog)
{
	int	res;

	pthread_mutex_lock(&prog->check_dead);
	res = prog->stop_simulation;
	pthread_mutex_unlock(&prog->check_dead);
	return (res);
}
