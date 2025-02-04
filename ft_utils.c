/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bekarada <bekarada@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 11:56:33 by bekarada          #+#    #+#             */
/*   Updated: 2025/02/03 17:59:53 by bekarada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atoi(const char *str)
{
	long	res;
	int		i;
	long	sign;

	sign = 1;
	i = 0;
	res = 0;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == ' '))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
		{
			sign *= -1;
		}
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (res * sign);
}

int	ft_isnum(char *str)
{
	int	i;

	if (str == NULL || str[0] == '\0')
		return (0);
	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_usleep(size_t mls)
{
	size_t	start;

	start = get_time();
	while (get_time() - start < mls)
		usleep(500);
}

void	write_msg(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->table->table_mutex);
	if (philo->table->completed_philos)
	{
		pthread_mutex_unlock(&philo->table->table_mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->table->table_mutex);
	pthread_mutex_lock(philo->write_mutex);
	printf("%zu %d %s\n", get_time() - philo->table->time_begin,
		philo->id, str);
	pthread_mutex_unlock(philo->write_mutex);
}
