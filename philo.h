/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hverda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 13:42:59 by hverda            #+#    #+#             */
/*   Updated: 2022/01/10 13:43:02 by hverda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>

# define DIED "\033[22;31m%lld %d died\033[0m\n"
# define THINKING "\033[22;37m%lld %d is thinking\033[0m\n"
# define SLEEPING "\033[22;36m%lld %d is sleeping\033[0m\n"
# define EATING "\033[22;33m%lld %d is eating\033[0m\n"
# define FIRST_FORK "\033[22;32m%lld %d has taken a fork\033[0m\n"
# define SECOND_FORK "\033[22;32m%lld %d has taken a fork\033[0m\n"
# define DONE "\033[22;35mall philosophers have already eaten\033[0m\n"

typedef struct s_philo
{
	int				id;
	long long		last_meal;
	int				times_to_eat;	
	int				first_fork;
	int				second_fork;
	struct s_table	*table;
	pthread_t		thread;
}	t_philo;

typedef struct s_table
{
	int				num_philos;
	long long		time_to_life;
	long long		time_to_eat;
	long long		time_to_sleep;
	int				num_eat;
	long long		start;
	int				flag;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
}	t_table;

long long	ft_atoi(const char *str);
long long	ft_util_atoi(const char *str);
long long	get_time(void);
void		ft_usleep(long long time);
void		ft_free(t_table *table);
void		ft_schedule(t_table *table, t_philo *philos);
void		one_philo(t_table *table, t_philo *philos);
void		*ft_thread(void *tmp);
void		ft_init_ph(t_table *table, t_philo *philos, int argc, char **argv);
void		ft_init_threads(t_table *table, t_philo *philos);
void		ft_init_mutex(t_table *table);
void		ft_die(t_table *table, t_philo *philos, int i, char *tmp);
void		ft_done(t_table *table);
void		ft_control(t_table *table, t_philo *philos);
int			ft_error(int argc, char **argv);
int			main(int argc, char **argv);

#endif
