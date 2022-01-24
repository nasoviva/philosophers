/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hverda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 13:43:06 by hverda            #+#    #+#             */
/*   Updated: 2022/01/10 13:43:09 by hverda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_die(t_table *table, t_philo *philos, int i, char *tmp)
{
	usleep(500);
	pthread_mutex_lock(&table->print);
	printf(tmp, (get_time() - table->start), philos[i].id);
	table->flag = 1;
}

void	ft_done(t_table *table)
{
	usleep(10000);
	table->flag = 1;
	pthread_mutex_lock(&table->print);
	printf(DONE);
}

void	ft_control(t_table *table, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < table->num_philos && table->flag != 1)
	{
		if (philos[i].last_meal != 0 && \
		get_time() - philos[i].last_meal > table->time_to_life \
		&& table->flag != 1)
		{
			ft_die(table, philos, i, DIED);
			break ;
		}
		if (philos[i].times_to_eat == 0)
			table->num_eat--;
		if (table->num_eat == 0)
		{
			ft_done(table);
			break ;
		}
		i++;
		if (i >= table->num_philos && table->flag != 1)
			i = 0;
		usleep(500);
	}
}

int	ft_error(int argc, char **argv)
{
	if (argc > 6 || argc < 5)
	{
		printf("Error number of args\n");
		return (1);
	}
	else if (ft_atoi(argv[1]) == -1 || ft_atoi(argv[2]) == -1 || \
	ft_atoi(argv[3]) == -1 || ft_atoi(argv[4]) == -1)
	{
		printf("Error args\n");
		return (1);
	}
	else if (ft_atoi(argv[1]) == 0 || ft_atoi(argv[2]) == 0 || \
	ft_atoi(argv[3]) == 0 || ft_atoi(argv[4]) == 0)
	{
		printf("Error args\n");
		return (1);
	}
	else if (argv[5] && (ft_atoi(argv[5]) == -1 || ft_atoi(argv[5]) == 0))
	{
		printf("Error args\n");
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_table	*table;
	t_philo	*philos;

	if (!(ft_error(argc, argv)))
	{
		table = malloc(sizeof(t_table));
		if (!table)
			return (1);
		table->num_philos = ft_atoi(argv[1]);
		philos = malloc(sizeof(t_philo) * table->num_philos);
		if (!philos)
			return (1);
		table->forks = malloc(sizeof(pthread_mutex_t) * table->num_philos);
		if (!table->forks)
			return (1);
		ft_init_mutex(table);
		ft_init_ph(table, philos, argc, argv);
		ft_init_threads(table, philos);
		ft_control(table, philos);
		ft_free (table);
	}
	return (0);
}
