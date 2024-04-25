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
	int		first;

	philo = data;
	first = 1;
	while (!is_other_dead(philo))
	{
		if (is_dead_monitor(philo))
		{
			flag_is_dead(philo);
			print_log("is dead", philo);
			break ;
		}
		if (first && philo->info->max_eat >= philo->info->limit_of_eating \
			&& philo->info->limit_of_eating != -1)
		{
			flag_ate_all(philo, &first);
			break ;
		}
		usleep(3000);
	}
	return (NULL);
}

void	free_all(t_info *info, t_philo *philo)
{
	int	i;

	pthread_mutex_destroy(info->print);
	pthread_mutex_destroy(info->last);
	pthread_mutex_destroy(info->repeat);
	pthread_mutex_destroy(info->stop);
	pthread_mutex_destroy(info->last_meal);
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
	free(info->last);
	free(info->repeat);
	free(info->print);
	free(info->stop);
	free(info->last_meal);
	free(philo);
}
