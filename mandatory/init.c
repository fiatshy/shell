/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghyki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 08:21:20 by sunghyki          #+#    #+#             */
/*   Updated: 2024/04/22 08:21:23 by sunghyki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_info_nested(t_info *info, int ac, int temp[5])
{
	info->total = temp[0];
	info->time_before_death = temp[1];
	info->time_of_eating = temp[2];
	info->time_of_sleeping = temp[3];
	if (ac == 6)
		info->limit_of_eating = temp[4] * info->total;
	else
		info->limit_of_eating = -1;
	info->max_eat = 0;
	info->is_dead = 0;
	info->pt = malloc (sizeof(pthread_t) * info->total);
	info->forks = malloc (sizeof(pthread_mutex_t) * info->total);
}

void	init_info(t_info *info, int ac, char **av)
{
	int	i;
	int	temp[5];

	i = 0;
	while (i < (ac - 1))
	{
		temp[i] = atoi(av[i + 1]);
		if (temp[i] == 0 && av[i + 1] != 0)
		{
			printf("Only decimal value is allowed\n");
			exit(1);
		}
		i++;
	}
	init_info_nested(info, ac, temp);
}

void	init_mutex(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->total)
	{
		pthread_mutex_init(&info->forks[i], NULL);
		i++;
	}
	info->death = malloc (sizeof(pthread_mutex_t));
	info->stop = malloc (sizeof(pthread_mutex_t));
	info->print = malloc (sizeof(pthread_mutex_t));
	pthread_mutex_init(info->death, NULL);
	pthread_mutex_init(info->stop, NULL);
	pthread_mutex_init(info->print, NULL);
}

void	init_philo(t_info *info, t_philo **philo)
{
	int	i;

	*philo = malloc (sizeof(t_philo) * info->total);
	i = 0;
	while (i < info->total)
	{
		(*philo)[i].id = i;
		(*philo)[i].left = i;
		(*philo)[i].right = (i + 1) % info->total;
		(*philo)[i].info = info;
		(*philo)[i].is_dead = 0;
		(*philo)[i].sync = malloc (sizeof(pthread_mutex_t));
		pthread_mutex_init((*philo)[i].sync, NULL);
		i++;
	}
}

void	run_thread(t_info *info, t_philo *philo)
{
	int	i;

	info->start_stamp = timestamp();
	pthread_mutex_lock(info->stop);
	i = 0;
	while (i < info->total)
	{
		pthread_create(&info->pt[i], NULL, daily, &philo[i]);
		pthread_detach(info->pt[i]);
		usleep(1000);
		i++;
	}
}
