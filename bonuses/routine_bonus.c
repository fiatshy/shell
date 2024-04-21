/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bouns.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghyki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:20:13 by sunghyki          #+#    #+#             */
/*   Updated: 2024/04/19 15:20:16 by sunghyki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	take_fork(t_philo *philo)
{
	struct timeval	now;

	sem_wait(philo->info->forks);
	print_log("has taken a fork ", philo);
	sem_wait(philo->info->forks);
	print_log("has taken a fork", philo);
	print_log("is eating", philo);
	usleep(philo->info->time_of_eating);
}

void	drop_fork_and_sleep(t_philo	*philo)
{
	struct timeval	now;

	philo->ate += 1;
	philo->eat_stamp = get_timestamp() - philo->start_time;
	philo->eat_stamp_sec = now.tv_sec;
	sem_post(philo->info->forks);
	sem_post(philo->info->forks);
	print_log("is sleeping", philo);
	usleep(philo->info->time_of_sleeping);
}

void	daily(t_philo *philo)
{
	pthread_t	death;

	philo->start_time = get_timestamp();
	philo->eat_stamp = get_timestamp() - philo->start_time + 1;
	pthread_create(&death, NULL, monitor_death, philo);
	pthread_detach(death);
	while (1)
	{
		take_fork(philo);
		drop_fork_and_sleep(philo);
		print_log("is thinking", philo);
	}
}
