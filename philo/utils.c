/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghyki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 08:58:57 by sunghyki          #+#    #+#             */
/*   Updated: 2024/04/25 08:59:00 by sunghyki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_dead_monitor(t_philo *philo)
{
	long	temp_stamp;

	pthread_mutex_lock(philo->info->last_meal);
	temp_stamp = timestamp() - philo->info->start_stamp;
	temp_stamp -= philo->eat_stamp;
	pthread_mutex_unlock(philo->info->last_meal);
	if (temp_stamp > philo->info->time_before_death)
		return (1);
	return (0);
}

int	is_other_dead(t_philo *philo)
{
	pthread_mutex_lock(philo->info->stop);
	if (philo->info->is_dead)
	{
		pthread_mutex_unlock(philo->info->stop);
		return (1);
	}
	pthread_mutex_unlock(philo->info->stop);
	return (0);
}

void	flag_is_dead(t_philo *philo)
{
	pthread_mutex_lock(philo->info->stop);
	philo->info->is_dead = 1;
	pthread_mutex_unlock(philo->info->stop);
}

void	flag_ate_all(t_philo *philo, int *first)
{
	pthread_mutex_lock(philo->info->stop);
	philo->info->is_dead = 1;
	*first = 0;
	pthread_mutex_unlock(philo->info->stop);
}
