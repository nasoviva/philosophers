/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hverda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 13:43:24 by hverda            #+#    #+#             */
/*   Updated: 2022/01/10 13:43:26 by hverda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	ft_util_atoi(const char *str)
{
	long int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if ((str[i] < '0' || str[i] > '9') && str[i] != '-' && str[i] != '+')
		{
			if ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
				i++;
			else
				return (1);
		}
		i++;
	}
	return (0);
}

long long	ft_atoi(const char *str)
{
	long long	r;
	int			z;

	r = 0;
	z = ft_util_atoi(str);
	while (*str != '\0')
	{
		if ((*str >= 9 && *str <= 13) || *str == 32)
			str++;
		if (*str == '-')
			z++;
		if (z >= 1)
			return (-1);
		if (*str >= '0' && *str <= '9')
			r = (r * 10) + (*str - 48);
		str++;
	}
	return (r);
}

long long	get_time(void)
{
	struct timeval	te;
	long long		milliseconds;

	gettimeofday(&te, NULL);
	milliseconds = te.tv_sec * 1000 + te.tv_usec / 1000;
	return (milliseconds);
}

void	ft_usleep(long long time)
{
	long long	result;
	long long	start;

	start = get_time();
	result = start + time;
	while (start < result)
	{
		start = get_time();
		usleep(100);
	}
}

void	ft_free(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philos)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&table->print);
}
