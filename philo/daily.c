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

int	is_dead(t_philo *philo)
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

void	custom_sleep(long duration, t_philo *philo)
{
	while (duration > 0)
	{
		pthread_mutex_lock(philo->info->stop);
		if (philo->info->is_dead)
		{
			pthread_mutex_unlock(philo->info->stop);
			break ;
		}
		else
			pthread_mutex_unlock(philo->info->stop);
		duration -= 1;
		usleep(850);
	}
}

void	take_fork_and_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->forks[philo->left]);
	print_log("has taken a fork", philo);
	pthread_mutex_lock(&philo->info->forks[philo->right]);
	print_log("has taken a fork", philo);
	if (is_dead(philo))
	{
		pthread_mutex_unlock(&philo->info->forks[philo->left]);
		pthread_mutex_unlock(&philo->info->forks[philo->right]);
		return ;
	}
	print_log("is eating", philo);
	philo->info->max_eat += 1;
	pthread_mutex_lock(philo->info->last_meal);
	philo->eat_stamp = timestamp() - philo->info->start_stamp;
	pthread_mutex_unlock(philo->info->last_meal);
	custom_sleep(philo->info->time_of_eating, philo);
	pthread_mutex_unlock(&philo->info->forks[philo->left]);
	pthread_mutex_unlock(&philo->info->forks[philo->right]);
}

void	philo_sleep(t_philo *philo)
{
	if (is_dead(philo))
		return ;
	print_log("is sleeping", philo);
	custom_sleep(philo->info->time_of_sleeping, philo);
	print_log("is thinking", philo);
}

void	*daily(void *data)
{
	t_philo		*philo;
	pthread_t	death;

	philo = data;
	philo->eat_stamp = timestamp() - philo->info->start_stamp;
	pthread_create(&death, NULL, ft_check_death, philo);
	if (philo->id % 2)
		usleep(philo->info->time_of_eating * 1000);
	if (philo->info->total == 1)
		print_log("has taken fork", philo);
	while (!is_dead(philo))
	{
		if (philo->info->total > 1)
		{
			take_fork_and_eat(philo);
			philo_sleep(philo);
		}
	}
	pthread_join(death, NULL);
	return (NULL);
}
