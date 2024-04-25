/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghyki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 08:21:52 by sunghyki          #+#    #+#             */
/*   Updated: 2024/04/22 08:21:56 by sunghyki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>

typedef struct s_info
{
	pthread_t		*pt;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*print;
	pthread_mutex_t	*last;
	pthread_mutex_t	*stop;
	pthread_mutex_t	*repeat;
	pthread_mutex_t	*last_meal;

	long			start_stamp;
	int				total;
	long			time_before_death;
	long			time_of_eating;
	long			time_of_sleeping;
	int				limit_of_eating;
	int				is_dead;
	int				max_eat;
}				t_info;

typedef struct s_philo
{
	pthread_mutex_t	*sync;
	t_info			*info;
	long			eat_stamp;
	int				id;
	int				right;
	int				left;
	int				is_dead;
	int				ate;
}				t_philo;

long	timestamp(void);
void	print_log(char *s, t_philo *philo);
void	*ft_check_death(void *data);
void	free_all(t_info *info, t_philo *philo);

void	take_fork_and_eat(t_philo *philo);
void	eat(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	*daily(void *data);

void	init_info(t_info *info, int ac, char **av);
void	init_mutex(t_info *info);
void	init_philo(t_info *info, t_philo **philo);
void	run_thread(t_info *info, t_philo *philo);

int		is_dead_monitor(t_philo *philo);
void	custom_sleep(long duration, t_philo *philo);
int		is_dead(t_philo *philo);

int		is_dead_monitor(t_philo *philo);
int		is_other_dead(t_philo *philo);
void	flag_is_dead(t_philo *philo);
void	flag_ate_all(t_philo *philo, int *first);

#endif
