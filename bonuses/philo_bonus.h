/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghyki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:19:49 by sunghyki          #+#    #+#             */
/*   Updated: 2024/04/19 15:19:59 by sunghyki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <semaphore.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <signal.h>
# include <sys/signal.h>
# include <unistd.h>

typedef struct s_info
{
	int		total;
	long	time_before_death;
	long	time_of_eating;
	long	time_of_sleeping;
	int		daily_limit;
	sem_t	*forks;
	sem_t	*print;
	sem_t	*death;
	sem_t	*stop;
	sem_t	*test;
}				t_info;

typedef struct s_philo
{
	t_info			*info;
	int				id;
	int				pid;
	long			start_time;
	long			eat_stamp;
	long			eat_stamp_sec;
	int				ate;
}				t_philo;

long	get_timestamp(void);
void	print_log(char *str, t_philo *philo);
void	post_singal_nested(t_philo *philo);
void	*monitor_death(void *data);

void	set_parameter(int ac, char **av, t_info *info);
void	set_semaphore(t_info *info);
void	set_philosopher(t_philo **philo, t_info *info);
void	fork_philosopher(t_philo *philo, t_info *info);
void	destory_philosopher(t_philo *philo, t_info *info);

void	take_fork(t_philo *philo);
void	drop_fork_and_sleep(t_philo	*philo);
void	daily(t_philo *philo);

#endif
