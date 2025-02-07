/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_actions.c                                       :+:      :+:    :+:   */
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
	if (philo->prog->must_eat > 0)
	{
		if (philo->times_ate < philo->prog->must_eat)
			return (0);
		else
			return (1);
	}
	return (0);
}

void	ft_print_msg(char *sms, t_philo *philo)
{
	if (pthread_mutex_lock(&philo->prog->msg_mutex) == 0)
	{
		if (!ft_stop_simulation(philo->prog) && !check_philo_eat(philo))
			printf("%ld %d %s\n",
				ft_time_diff(philo->start_time), philo->id, sms);
		pthread_mutex_unlock(&philo->prog->msg_mutex);
	}
}

void	ft_get_fork(t_philo *philo)
{
	if (!ft_stop_simulation(philo->prog) && !check_philo_eat(philo))
	{
		if (philo->id % 2 == 0)
		{
			pthread_mutex_lock(philo->left_fork);
			ft_print_msg("has taken a fork", philo);
			pthread_mutex_lock(philo->right_fork);
			ft_print_msg("has taken a fork", philo);
		}
		else
		{
			pthread_mutex_lock(philo->right_fork);
			ft_print_msg("has taken a fork", philo);
			pthread_mutex_lock(philo->left_fork);
			ft_print_msg("has taken a fork", philo);
		}
	}
	return ;
}

void	ft_philo_eat_and_sleep(t_philo *philo)
{
	ft_get_fork(philo);
	ft_print_msg("is eating", philo);
	ft_inform_time_ate(philo);
	ft_inform_last_time_ate(philo, ft_get_time());
	usleep(philo->prog->time_to_eat * 1000);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	if (!ft_stop_simulation(philo->prog))
	{
		ft_print_msg("sleeping", philo);
		usleep(philo->prog->time_to_sleep * 1000);
	}
}
