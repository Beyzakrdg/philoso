/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_threads.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bekarada <bekarada@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 12:15:21 by bekarada          #+#    #+#             */
/*   Updated: 2025/02/03 17:56:51 by bekarada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_destroy(t_table *table, char *str)
{
	int	i;

	i = 0;
	while (i++ < table->num_philos)
		pthread_mutex_destroy(&(table->forks[i]));
	pthread_mutex_destroy(&(table->meals_mutex));
	pthread_mutex_destroy(&(table->write_mutex));
	pthread_mutex_destroy(&(table->table_mutex));
	free(table->forks);
	free(table->philo);
	free(table);
	if (str)
		return (handle_error(str), 1);
	return (0);
}

static void	ft_wait_philo(t_table *table)
{
	int	i;

	i = 0;
	while (i++ < table->num_philos)
		pthread_join(table->philo[i].thread, NULL);
}

static	void	ft_monitor_init(t_table *table)
{
	if (pthread_create(&table->monitor, NULL, &ft_monitor, table->philo) != 0)
		ft_destroy(table, "Error\nThread not create\n");
}

static void	ft_init_philo(t_table *table, int i)
{
	if (pthread_create(&table->philo[i].thread, NULL,
			ft_routine_philo, &table->philo[i]) != 0)
		ft_destroy(table, "Error\nThread not create\n");
}

int	ft_create_threads(t_table *table)
{
	int	i;

	i = 0;
	pthread_mutex_init(&table->table_mutex, NULL);
	ft_monitor_init(table);
	while (i++ < table->num_philos)
		ft_init_philo(table, i);
	pthread_mutex_lock(&table->table_mutex);
	table->ready_philos = true;
	pthread_mutex_unlock(&table->table_mutex);
	ft_wait_philo(table);
	pthread_join(table->monitor, NULL);
	return (0);
}
