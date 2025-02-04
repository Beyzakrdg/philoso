/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_actions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bekarada <bekarada@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 11:32:53 by bekarada          #+#    #+#             */
/*   Updated: 2025/02/04 18:42:23 by bekarada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_philo_eat(t_philo *philo)
{
	if (philo->monitor->must_eat > 0)
	{
		if (philo->times_ate < philo->monitor->must_eat)
			return (0);
		else
			return (1);
	}
	return (0);
}

void	ft_print_message(char *sms, t_philo *philo)
{
	if (pthread_mutex_lock(&philo->monitor->message_mutex) == 0)
	{
		if (!ft_stop_simulation(philo->monitor) && !check_philo_eat(philo))
			printf("%ld %d %s\n",
				ft_time_diff(philo->start_time), philo->id_philo, sms);
		pthread_mutex_unlock(&philo->monitor->message_mutex);
	}
}

void	ft_get_fork(t_philo *philo)
{
	if (!ft_stop_simulation(philo->monitor) && !check_philo_eat(philo))
	{
		if (philo->id_philo % 2 == 0)
		{
			pthread_mutex_lock(philo->fork_r);
			ft_print_message("has taken a fork", philo);
			pthread_mutex_lock(philo->fork_l);
			ft_print_message("has taken a fork", philo);
		}
		else
		{
			pthread_mutex_lock(philo->fork_l);
			ft_print_message("has taken a fork", philo);
			pthread_mutex_lock(philo->fork_r);
			ft_print_message("has taken a fork", philo);
		}
	}
	return ;
}

void	ft_philo_eat_and_sleep(t_philo *philo)
{
	ft_get_fork(philo);
	ft_print_message("is eating", philo);
	ft_inform_time_ate(philo);
	ft_inform_last_time_ate(philo, ft_set_time());
	usleep(philo->monitor->time_to_eat * 1000);
	pthread_mutex_unlock(philo->fork_l);
	pthread_mutex_unlock(philo->fork_r);
	if (!ft_stop_simulation(philo->monitor))
	{
		ft_print_message("sleeping", philo);
		usleep(philo->monitor->time_to_sleep * 1000);
	}
}
