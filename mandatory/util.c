/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghyki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 08:21:27 by sunghyki          #+#    #+#             */
/*   Updated: 2024/04/22 08:21:31 by sunghyki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	timestamp(void)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return (now.tv_sec * 1000 + now.tv_usec / 1000);
}

void	print_log(char *s, t_philo *philo)
{
	pthread_mutex_lock(philo->info->print);
	printf("%ld : %d %s\n", timestamp() - \
		philo->info->start_stamp, philo->id, s);
	pthread_mutex_unlock(philo->info->print);
}

void	*ft_check_death(void *data)
{
	t_philo	*philo;

	philo = data;
	while (1)
	{
		if (timestamp() - philo->info->start_stamp - \
			philo->eat_stamp > philo->info->time_before_death)
		{
			philo->info->is_dead = 1;
			pthread_mutex_lock(philo->sync);
			print_log("is dead", philo);
			pthread_mutex_unlock(philo->info->stop);
			break ;
		}
		if (philo->info->max_eat == philo->info->limit_of_eating)
		{
			philo->info->is_dead = 1;
			pthread_mutex_lock(philo->sync);
			pthread_mutex_unlock(philo->info->stop);
			break ;
		}
	}
	return (NULL);
}

void	free_all(t_info *info, t_philo *philo)
{
	int	i;

	pthread_mutex_destroy(info->death);
	pthread_mutex_destroy(info->stop);
	i = 0;
	while (i < info->total)
	{
		pthread_mutex_destroy(&info->forks[i]);
		pthread_mutex_destroy(philo[i].sync);
		free(philo[i].sync);
		i++;
	}
	free(info->forks);
	free(info->pt);
	free(info->death);
	free(info->print);
	free(info->stop);
	free(philo);
}
