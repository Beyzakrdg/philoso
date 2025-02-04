/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_monitor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bekarada <bekarada@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 07:22:23 by hugozlu           #+#    #+#             */
/*   Updated: 2025/02/04 18:42:35 by bekarada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_all_philos_have_ate(t_philo *philo, t_monitor *monitor)
{
	int		i;

	i = 0;
	while (i < monitor->nbr_of_philo)
	{
		if (ft_check_times_ate(&philo[i]) < monitor->must_eat)
			return (0);
		i++;
	}
	if (monitor->must_eat > 0)
	{
		ft_inform_stop_simulation(monitor, 1);
		return (1);
	}
	return (0);
}

static	int	ft_set_philo_dead(t_monitor *monitor, t_philo *philo)
{
	int	index;

	index = -1;
	while (++index < monitor->nbr_of_philo)
	{
		if ((ft_set_time() - ft_check_last_time_ate(&philo[index]))
			> monitor->time_to_die + 2)
		{
			ft_print_message("died", &philo[index]);
			ft_inform_stop_simulation(monitor, 1);
			return (1);
		}
	}
	return (0);
}

void	*ft_monitor(void *arg)
{
	t_monitor		*monitor;
	t_philo			*philo;

	philo = (t_philo *)arg;
	monitor = philo[0].monitor;
	while (!ft_stop_simulation(monitor))
	{
		if (ft_set_philo_dead(monitor, philo))
			break ;
		if (ft_all_philos_have_ate(philo, monitor))
			break ;
		usleep(1000);
	}
	return (NULL);
}
