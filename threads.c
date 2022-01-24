/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hverda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 13:43:15 by hverda            #+#    #+#             */
/*   Updated: 2022/01/10 13:43:17 by hverda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_schedule(t_table *table, t_philo *philos)
{
	pthread_mutex_lock(&table->forks[philos->first_fork]);
	pthread_mutex_lock(&table->print);
	printf(FIRST_FORK, (get_time() - table->start), philos->id);
	pthread_mutex_unlock(&table->print);
	pthread_mutex_lock(&table->forks[philos->second_fork]);
	pthread_mutex_lock(&table->print);
	printf(SECOND_FORK, (get_time() - table->start), philos->id);
	pthread_mutex_unlock(&table->print);
	pthread_mutex_lock(&table->print);
	philos->last_meal = get_time();
	printf(EATING, (get_time() - table->start), philos->id);
	pthread_mutex_unlock(&table->print);
	ft_usleep(table->time_to_eat);
	pthread_mutex_unlock(&table->forks[philos->second_fork]);
	pthread_mutex_unlock(&table->forks[philos->first_fork]);
	pthread_mutex_lock(&table->print);
	printf(SLEEPING, (get_time() - table->start), philos->id);
	pthread_mutex_unlock(&table->print);
	usleep(table->time_to_sleep * 1000);
	pthread_mutex_lock(&table->print);
	printf(THINKING, (get_time() - table->start), philos->id);
	pthread_mutex_unlock(&table->print);
}

void	one_philo(t_table *table, t_philo *philos)
{
	if (table->num_philos == 1)
	{
		pthread_mutex_lock(&table->forks[philos->first_fork]);
		pthread_mutex_lock(&table->print);
		printf(FIRST_FORK, (get_time() - table->start), philos->id);
		pthread_mutex_unlock(&table->print);
		philos->last_meal = get_time();
	}
}

void	*ft_thread(void *tmp)
{
	t_philo	*philos;

	philos = (t_philo *)tmp;
	if (philos->table->num_philos == 1)
		one_philo(philos->table, philos);
	else if (philos->table->num_philos > 1 && philos->times_to_eat != 0)
	{		
		if (philos->id % 2 != 0)
			usleep((philos->table->time_to_eat / 2) * 1000);
		while (philos->table->flag != 1)
		{		
			ft_schedule(philos->table, philos);
			if (philos->times_to_eat > 0)
				philos->times_to_eat--;
		}
	}
	return (NULL);
}
