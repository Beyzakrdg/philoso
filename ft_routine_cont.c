/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_routine_cont.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bekarada <bekarada@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 16:04:02 by bekarada          #+#    #+#             */
/*   Updated: 2025/02/03 16:41:27 by bekarada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_philo *philo)
{
	write_msg(philo, "is eating");
	ft_usleep(philo->time_to_eat);
	pthread_mutex_lock(philo->meal_mutex);
	philo->last_meal = get_time();
	philo->eaten_meal++;
	pthread_mutex_unlock(philo->meal_mutex);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	sleeping(t_philo *philo)
{
	write_msg(philo, "is sleeping");
	ft_usleep(philo->time_to_sleep);
	write_msg(philo, "is thinking");
}

void	taking(t_philo *philo, pthread_mutex_t *fork)
{
	pthread_mutex_lock(fork);
	write_msg(philo, "has taken a fork");
}
