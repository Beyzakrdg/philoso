/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_monitor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bekarada <bekarada@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 16:05:45 by bekarada          #+#    #+#             */
/*   Updated: 2025/02/03 18:31:49 by bekarada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_set_last_meal(t_table *table)
{
	int		i;
	t_philo	*philos;

	i = 0;
	philos = table->philo;
	while (i < table->num_philos)
	{
		pthread_mutex_lock(&table->meals_mutex);
		philos[i].last_meal = table->time_begin;
		pthread_mutex_unlock(&table->meals_mutex);
		i++;
	}
	return (0);
}

static int	all_philo_ate(t_philo *philos)
{
	int	i;
	int	finished;

	if (philos[0].count_eat == -1)
		return (0);
	i = 0;
	finished = 0;
	while (i < philos[0].nbr_of_philo)
	{
		pthread_mutex_lock(philos[i].meal_mutex);
		if (philos[i].eaten_meal >= philos[i].count_eat)
			finished++;
		pthread_mutex_unlock(philos[i].meal_mutex);
		i++;
	}
	if (finished == philos[0].nbr_of_philo)
		return (1);
	return (0);
}

static bool	ft_one_philo_checker(t_philo *philo, t_table *table)
{
	size_t	time_since_last_meal;

	pthread_mutex_lock(philo->meal_mutex);
	time_since_last_meal = get_time() - philo->last_meal;
	if (time_since_last_meal > philo->time_to_die)
	{
		table->completed_philos = true;
		pthread_mutex_lock(philo->write_mutex);
		printf("%lu %d %s\n",
			get_time() - table->time_begin,
			philo->id, "died");
		pthread_mutex_unlock(philo->write_mutex);
		pthread_mutex_unlock(philo->meal_mutex);
		return (true);
	}
	pthread_mutex_unlock(philo->meal_mutex);
	return (false);
}

static void	ft_init_monitor(t_philo *philos)
{
	t_table	*table;

	table = philos[0].table;
	if (!table)
	{
		handle_error("Error\nTable pointer is NULL\n");
		return ;
	}
	while (table->ready_philos != true)
	{
		pthread_mutex_unlock(&table->table_mutex);
		usleep(100);
		pthread_mutex_lock(&table->table_mutex);
	}
	pthread_mutex_unlock(&table->table_mutex);
	pthread_mutex_lock(&table->table_mutex);
	table->time_begin = get_time();
	pthread_mutex_unlock(&table->table_mutex);
	ft_set_last_meal(table);
	pthread_mutex_lock(&table->table_mutex);
	table->ready_monitor = true;
	pthread_mutex_unlock(&table->table_mutex);
}

void	*ft_monitor(void *philo_void)
{
	t_philo		*philos;
	t_table		*table;
	int			i;

	philos = (t_philo *)philo_void;
	table = philos[0].table;
	ft_init_monitor(philos);
	while (1)
	{
		i = 0;
		while (i++ < philos[0].nbr_of_philo)
		{
			if (ft_one_philo_checker(&philos[i], table))
				return (NULL);
		}
		if (all_philo_ate(philos) == 1)
		{
			table->completed_philos = true;
			return (NULL);
		}
	}
	return (NULL);
}
