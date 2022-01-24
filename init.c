/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hverda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 12:15:48 by hverda            #+#    #+#             */
/*   Updated: 2022/01/12 12:15:50 by hverda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_init_ph(t_table *table, t_philo *philos, int argc, char **argv)
{
	int	i;

	i = 0;
	table->flag = 0;
	table->num_eat = table->num_philos;
	table->time_to_life = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	while (i < table->num_philos)
	{
		philos[i].id = i + 1;
		philos[i].last_meal = 0;
		philos[i].first_fork = (i + 1) % table->num_philos;
		philos[i].second_fork = i;
		philos[i].table = table;
		if (argc == 6)
			philos[i].times_to_eat = ft_atoi(argv[5]);
		else
			philos[i].times_to_eat = -1;
		i++;
	}
}

void	ft_init_threads(t_table *table, t_philo *philos)
{
	int	i;

	i = 0;
	table->start = get_time();
	while (i < table->num_philos)
	{
		pthread_create(&philos[i].thread, NULL, ft_thread, \
		&philos[i]);
		i++;
	}
}

void	ft_init_mutex(t_table *table)
{
	int		i;

	i = 0;
	while (i < table->num_philos)
	{
		pthread_mutex_init(&table->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&table->print, NULL);
}
