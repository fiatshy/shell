/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghyki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:20:24 by sunghyki          #+#    #+#             */
/*   Updated: 2024/04/19 15:20:27 by sunghyki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long	get_timestamp(void)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return (now.tv_sec * 1000 + now.tv_usec / 1000);
}

void	print_log(char *str, t_philo *philo)
{
	struct timeval	now;

	sem_wait(philo->info->print);
	printf("%ld : %d %s\n", get_timestamp() - philo->start_time, philo->id, str);
	sem_post(philo->info->print);
}

void	post_singal_nested(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->info->total * 2)
	{
		sem_post(philo->info->stop);
		i++;
	}
}

void	*monitor_death(void *data)
{
	t_philo			*philo;
	int				reached_limit;
	int				first;
	struct timeval	now;

	reached_limit = 0;
	philo = (t_philo *)data;
	first = 1;
	while (1)
	{
		sem_wait(philo->info->death);
		if (first && (get_timestamp() - philo->start_time - philo->eat_stamp > \
			philo->info->time_before_death / 1000) && philo->eat_stamp != 0)
		{
			print_log("is dead", philo);
			first = 0;
			post_singal_nested(philo);
		}
		if (philo->ate == philo->info->daily_limit && !reached_limit)
		{
			reached_limit = 1;
			sem_post(philo->info->stop);
		}
		sem_post(philo->info->death);
	}
}
