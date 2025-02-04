/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bekarada <bekarada@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 07:22:17 by hugozlu           #+#    #+#             */
/*   Updated: 2025/02/04 18:47:59 by bekarada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_routine_case_one_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->fork_r);
	ft_print_message("has taken a fork", philo);
	usleep(philo->monitor->time_to_die * 1000);
	pthread_mutex_unlock(philo->fork_r);
}

void	*ft_routine(void *arg)
{
	t_philo			*philo;

	philo = (t_philo *)arg;
	if (philo->monitor->nbr_of_philo == 1)
	{
		ft_routine_case_one_philo(philo);
		return (NULL);
	}
	while (!ft_stop_simulation(philo->monitor))
	{
		ft_philo_eat_and_sleep(philo);
		ft_print_message("thinking", philo);
	}
	return (NULL);
}

static int	ft_checkarg(int argc, char **argv)
{
	int	i;

	i = 0;
	while (argv[++i])
		if (ft_find_alpha_in_list(argv[i]))
			return (printf("Invalid arguments\n"), 1);
	if (argc == 1)
		return (1);
	else if ((argc == 5) || (argc == 6))
	{
		if (ft_atoi(argv[1]) > MAX)
			return (printf("To exceded number of philos\n"), 1);
		return (0);
	}
	else if (argc < 6)
		return (printf("To few arguments\n"), 1);
	else
		return (printf("To Many arguments\n"), 1);
	return (0);
}

int	ft_assign(int argc, char **argv, t_monitor *monitor)
{
	if (ft_checkarg(argc, argv))
		return (1);
	monitor->nbr_of_philo = ft_atoi(argv[1]);
	monitor->time_to_die = ft_atoi(argv[2]);
	monitor->time_to_eat = ft_atoi(argv[3]);
	monitor->time_to_sleep = ft_atoi(argv[4]);
	monitor->stop_simulation = 0;
	if (argv[5])
		monitor->must_eat = ft_atoi(argv[5]);
	else
		monitor->must_eat = 0;
	return (0);
}

int	main(int argc, char **argv)
{
	t_monitor			monitor;
	t_philo				*philo;
	pthread_mutex_t		*forks;

	if (ft_assign(argc, argv, &monitor) == 1)
		return (0);
	ft_init_monitor_mutexes(&monitor);
	philo = (t_philo *)malloc(sizeof(t_philo) * monitor.nbr_of_philo);
	if (!philo)
		return (1);
	forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* monitor.nbr_of_philo);
	if (!forks)
		return (1);
	ft_init_mutexes(forks, monitor.nbr_of_philo);
	ft_init_philos(&monitor, philo, forks);
	if (pthread_create(&monitor.monitor_thread, NULL, ft_monitor, philo) != 0)
		return (ft_putstr_fd("failed to create  a tread", 2), 1);
	ft_create_and_join_philo(philo, monitor.nbr_of_philo);
	if (pthread_join(monitor.monitor_thread, NULL) != 0)
		return (ft_putstr_fd("failde to join a thread", 2), 1);
	ft_destroy_mutexes(forks, monitor.nbr_of_philo);
	ft_destroy_monitor(&monitor);
	free(philo);
	free(forks);
	return (0);
}
