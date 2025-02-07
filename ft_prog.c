/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prog.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bekarada <bekarada@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 07:22:23 by bekarada          #+#    #+#             */
/*   Updated: 2025/02/04 18:42:35 by bekarada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_all_philos_have_ate(t_philo *philo, t_prog *prog)
{
	int		i;

	i = 0;
	while (i < prog->nbr_of_philo)
	{
		if (ft_check_times_ate(&philo[i]) < prog->must_eat)
			return (0);
		i++;
	}
	if (prog->must_eat > 0)
	{
		ft_inform_stop_simulation(prog, 1);
		return (1);
	}
	return (0);
}

static	int	ft_set_philo_dead(t_prog *prog, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < prog->nbr_of_philo)
	{
		if ((ft_get_time() - ft_check_last_time_ate(&philo[i]))
			> prog->time_to_die + 2)
		{
			ft_print_msg("died", &philo[i]);
			ft_inform_stop_simulation(prog, 1);
			return (1);
		}
		i++;
	}
	return (0);
}

void	*ft_program(void *arg)
{
	t_prog	*prog;
	t_philo	*philo;

	philo = (t_philo *)arg;
	prog = philo[0].prog;
	while (!ft_stop_simulation(prog))
	{
		if (ft_set_philo_dead(prog, philo))
			break ;
		if (ft_all_philos_have_ate(philo, prog))
			break ;
		usleep(1000);
	}
	return (NULL);
}
