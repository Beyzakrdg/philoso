/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bekarada <bekarada@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 11:32:53 by bekarada          #+#    #+#             */
/*   Updated: 2025/02/04 18:42:23 by bekarada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_one_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	ft_print_msg("has taken a fork", philo);
	usleep(philo->prog->time_to_die * 1000);
	pthread_mutex_unlock(philo->right_fork);
}

void	*ft_routine(void *arg)
{
	t_philo			*philo;

	philo = (t_philo *)arg;
	if (philo->prog->nbr_of_philo == 1)
	{
		ft_one_philo(philo);
		return (NULL);
	}
	while (!ft_stop_simulation(philo->prog))
	{
		ft_philo_eat_and_sleep(philo);
		ft_print_msg("thinking", philo);
	}
	return (NULL);
}

static int	ft_checkarg(int argc, char *argv[])
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (!ft_isnum(argv[i]))
			return (printf("Error\nInvalid arguments\n"), 1);
		i++;
	}
	if (argc == 1)
		return (1);
	else if ((argc == 5) || (argc == 6))
	{
		if (ft_atoi(argv[1]) > 200)
			return (printf("Error\nWrong philo number\n"), 1);
		if (ft_atoi(argv[1]) <= 0 || ft_atoi(argv[2]) <= 0 || ft_atoi(argv[3]) <= 0 || ft_atoi(argv[4]) <= 0)
			return (printf("Error\nWrong number\n"), 1);
		if (argc == 6 && (ft_atoi(argv[5]) <= 0))
			return (printf("Error\nWrong number\n"), 1);
		return (0);
	}
	else if (argc < 6)
		return (printf("Error\nTo few arguments\n"), 1);
	else
		return (printf("Error\nTo many arguments\n"), 1);
	return (0);
}

int	ft_assign(int argc, char *argv[], t_prog *prog)
{
	if (ft_checkarg(argc, argv))
		return (1);
	prog->nbr_of_philo = ft_atoi(argv[1]);
	prog->time_to_die = ft_atoi(argv[2]);
	prog->time_to_eat = ft_atoi(argv[3]);
	prog->time_to_sleep = ft_atoi(argv[4]);
	prog->stop_simulation = 0;
	if (argv[5])
		prog->must_eat = ft_atoi(argv[5]);
	else
		prog->must_eat = 0;
	return (0);
}

int	main(int argc, char *argv[])
{
	t_prog				prog;
	t_philo				*philo;
	pthread_mutex_t		*forks;

	if (ft_assign(argc, argv, &prog) == 1)
		return (1);
	ft_init_prog_mutexes(&prog);
	philo = (t_philo *)malloc(sizeof(t_philo) * prog.nbr_of_philo);
	if (!philo)
		return (1);
	forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* prog.nbr_of_philo);
	if (!forks)
		return (1);
	ft_init_fork_mutexes(forks, prog.nbr_of_philo);
	ft_init_philos(&prog, philo, forks);
	if (pthread_create(&prog.prog_thread, NULL, ft_program, philo) != 0)
		return (printf("Error\nfailed to create  a tread"), 1);
	ft_create_and_join_philo(philo, prog.nbr_of_philo);
	if (pthread_join(prog.prog_thread, NULL) != 0)
		return (printf("Error\nfailde to join a thread"), 1);
	ft_destroy_mutexes(forks, prog.nbr_of_philo);
	ft_destroy_prog(&prog);
	free(philo);
	free(forks);
	return (0);
}
