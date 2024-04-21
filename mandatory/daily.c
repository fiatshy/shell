/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   daily.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghyki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 08:21:15 by sunghyki          #+#    #+#             */
/*   Updated: 2024/04/22 08:21:17 by sunghyki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->forks[philo->left]);
	print_log("has taken a fork 1", philo);
	pthread_mutex_lock(&philo->info->forks[philo->right]);
	print_log("has taken a fork 2", philo);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->sync);
	print_log("is eating", philo);
	philo->eat_stamp = timestamp() - philo->info->start_stamp;
	philo->info->max_eat += 1;
	usleep(philo->info->time_of_eating * 1000);
	pthread_mutex_unlock(&philo->info->forks[philo->left]);
	pthread_mutex_unlock(&philo->info->forks[philo->right]);
	pthread_mutex_unlock(philo->sync);
}

void	philo_sleep(t_philo *philo)
{
	print_log("is sleeping", philo);
	usleep(philo->info->time_of_sleeping * 1000);
	print_log("is thinking", philo);
}

void	*daily(void *data)
{
	t_philo		*philo;
	pthread_t	death;

	philo = data;
	philo->eat_stamp = timestamp() - philo->info->start_stamp + 1;
	pthread_create(&death, NULL, ft_check_death, philo);
	pthread_detach(death);
	if (philo->id % 2)
		usleep(philo->info->time_of_eating * 1000);
	while (1)
	{
		if (philo->info->is_dead == 1)
		{
			break ;
		}
		take_fork(philo);
		eat(philo);
		philo_sleep(philo);
	}
	return (NULL);
}
