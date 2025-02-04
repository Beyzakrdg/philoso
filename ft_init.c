/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bekarada <bekarada@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 11:32:53 by bekarada          #+#    #+#             */
/*   Updated: 2025/02/03 18:20:42 by bekarada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	fork_mutex(t_table **table)
{
	int				i;
	pthread_mutex_t	*forks;

	i = 0;
	forks = (*table)->forks;
	while (i < (*table)->num_philos)
		pthread_mutex_init(&forks[i++], NULL);
	i = 0;
	while (i++ < (*table)->num_philos)
	{
		(*table)->philo[i].left_fork = &forks[i];
		(*table)->philo[i].right_fork = &forks[(i + 1) % (*table)->num_philos];
	}
}

void	ft_init(t_table **table, int philo_number)
{
	*table = malloc(sizeof(t_table));
	if (!*table)
		return ;
	(*table)->num_philos = philo_number;
	(*table)->ready_philos = false;
	pthread_mutex_init(&(*table)->meals_mutex, NULL);
	pthread_mutex_init(&(*table)->write_mutex, NULL);
	pthread_mutex_init(&(*table)->table_mutex, NULL);
	(*table)->philo = malloc(sizeof(t_philo) * philo_number);
	if (!(*table)->philo)
	{
		free(*table);
		return ;
	}
	(*table)->forks = malloc(sizeof(pthread_mutex_t) * philo_number);
	if (!(*table)->forks)
	{
		free((*table)->philo);
		free(*table);
		return ;
	}
	fork_mutex(table);
}
