/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bekarada <bekarada@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 17:30:18 by bekarada          #+#    #+#             */
/*   Updated: 2025/02/04 13:35:40 by bekarada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	handle_error(char *str)
{
	if (str)
		write(2, str, (ft_strlen(str) + 1));
}

static void	ft_assign(int argc, char *argv[], t_table *table)
{
	int	i;
	int	philo_number;

	i = 0;
	philo_number = ft_atoi(argv[1]);
	while (i++ < philo_number)
	{
		table->philo[i].id = i + 1;
		table->philo[i].eat_meal = 0;
		table->philo[i].eaten_meal = 0;
		table->philo[i].nbr_of_philo = philo_number;
		table->philo[i].time_to_die = ft_atoi(argv[2]);
		table->philo[i].time_to_eat = ft_atoi(argv[3]);
		table->philo[i].time_to_sleep = ft_atoi(argv[4]);
		table->philo[i].last_meal = get_time();
		table->philo[i].count_eat = -1;
		if (argc == 6)
			table->philo[i].count_eat = ft_atoi(argv[5]);
		table->philo[i].write_mutex = &(table->write_mutex);
		table->philo[i].meal_mutex = &(table->meals_mutex);
		table->philo[i].table = table;
	}
}

static int	ft_argcontrol(int argc, char *argv[])
{
	int	i;

	if (argc < 5 || argc > 6)
		handle_error("Error\nInvalid number of arguments\n");
	i = 1;
	while (i < argc)
	{
		if (!ft_isnum(argv[i]) || ft_atoi(argv[i]) < 1
			|| ft_atoi(argv[i]) > 2147483647)
			return (handle_error("Error\nInvalid argument values\n"), 1);
		i++;
	}
	if (ft_atoi(argv[1]) > 200 || ft_atoi(argv[2]) < 60 || ft_atoi(argv[3]) < 60
		|| ft_atoi(argv[4]) < 60)
		return (handle_error("Error\nWrong argument values\n"), 1);
	if (argc == 6 && ft_atoi(argv[5]) <= 0)
		return (handle_error("5th parameter cannot be below or equal 0\n"), 1);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_table	*table;

	table = NULL;
	if (ft_argcontrol(argc, argv) != 0)
		return (handle_error("Error\nArguments fail\n"), 1);
	ft_init(&table, ft_atoi(argv[1]));
	if (!table)
		return (1);
	ft_assign(argc, argv, table);
	ft_create_threads(table);
	ft_destroy(table, 0);
}
