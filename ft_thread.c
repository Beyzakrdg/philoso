/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_thread.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bekarada <bekarada@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 07:22:43 by bekarada          #+#    #+#             */
/*   Updated: 2025/02/04 18:42:56 by bekarada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_create_and_join_philo(t_philo *philo, int nbr_of_philo)
{
	int	i;

	i = 0;
	while (i < nbr_of_philo)
	{
		if (pthread_create(&philo[i].thread_nbr, NULL, &ft_routine,
				&philo[i]) != 0)
			return (printf("failed create philo"), 1);
		i++;
	}
	i = 0;
	while (i < nbr_of_philo)
	{
		if (pthread_join(philo[i].thread_nbr, NULL) != 0)
			return (printf("failed to join thread"), 1);
		i++;
	}
	return (0);
}
