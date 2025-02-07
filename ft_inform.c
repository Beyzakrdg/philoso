/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_inform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bekarada <bekarada@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 11:32:53 by bekarada          #+#    #+#             */
/*   Updated: 2025/02/04 18:42:19 by bekarada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_inform_stop_simulation(t_prog *prog, size_t value)
{
	pthread_mutex_lock(&prog->check_dead);
	prog->stop_simulation = value;
	pthread_mutex_unlock(&prog->check_dead);
}

void	ft_inform_last_time_ate(t_philo *philo, size_t value)
{
	pthread_mutex_lock(&philo->prog->check_last_meal);
	philo->last_time_ate = value;
	pthread_mutex_unlock(&philo->prog->check_last_meal);
}

void	ft_inform_time_ate(t_philo *philo)
{
	pthread_mutex_lock(&philo->prog->times_eat);
	philo->times_ate++;
	pthread_mutex_unlock(&philo->prog->times_eat);
}
