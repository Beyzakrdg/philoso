/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_mutexes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bekarada <bekarada@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 07:22:36 by hugozlu           #+#    #+#             */
/*   Updated: 2025/02/04 18:42:52 by bekarada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_destroy_mutexes(pthread_mutex_t *forks, int nbr_of_philo)
{
	int	i;

	i = 0;
	while (i < nbr_of_philo)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
}

void	ft_destroy_monitor(t_monitor *monitor)
{
	pthread_mutex_destroy(&monitor->message_mutex);
	pthread_mutex_destroy(&monitor->check_dead);
	pthread_mutex_destroy(&monitor->check_last_meal);
	pthread_mutex_destroy(&monitor->times_eat);
}
