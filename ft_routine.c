/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bekarada <bekarada@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:39:47 by bekarada          #+#    #+#             */
/*   Updated: 2025/02/03 16:49:32 by bekarada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	ft_philos_ready(t_table *table)
{
	if (table->ready_philos == true)
	{
		return (true);
	}
	return (false);
}

static bool	ft_monitor_ready(t_table *table)
{
	if (table->ready_monitor == true)
	{
		return (true);
	}
	return (false);
}

bool	ft_is_done(t_table *table)
{
	bool	is_done;

	pthread_mutex_lock(&table->table_mutex);
	is_done = table->completed_philos;
	pthread_mutex_unlock(&table->table_mutex);
	return (is_done);
}

static void	ft_one_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	write_msg(philo, "has taken a fork");
	pthread_mutex_unlock(philo->left_fork);
	return ;
}

void	*ft_routine_philo(void *philo)
{
	t_philo	*philos;

	philos = (t_philo *)philo;
	while (ft_philos_ready(philos->table) != true)
		;
	while (ft_monitor_ready(philos->table) != true)
		;
	if (philos->table->num_philos == 1)
	{
		ft_one_philo(philo);
		return (NULL);
	}
	if (philos->id % 2 != 0)
	{
		write_msg(philos, "is thinking");
		ft_usleep(1);
	}
	while (ft_is_done(philos->table) != true)
	{
		taking(philos, philos->left_fork);
		taking(philos, philos->right_fork);
		eating(philos);
		sleeping(philos);
	}
	return (NULL);
}
