/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghyki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:19:26 by sunghyki          #+#    #+#             */
/*   Updated: 2024/04/19 15:19:28 by sunghyki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	set_parameter(int ac, char **av, t_info *info)
{
	int	temp[5];
	int	i;

	i = 0;
	while (i < ac - 1)
	{
		if (i != 0 && i != 4)
			temp[i] = atoi(av[i + 1]) * 1000;
		else
			temp[i] = atoi(av[i + 1]);
		if (temp[i] == 0 && av[i + 1][0] != '0')
		{
			printf("Only decimal argument is allowed.");
			exit(1);
		}
		i++;
	}
	info->total = temp[0];
	info->time_before_death = temp[1];
	info->time_of_eating = temp[2];
	info->time_of_sleeping = temp[3];
	if (ac == 6)
		info->daily_limit = temp[4];
	else
		info->daily_limit = -1;
}

void	set_semaphore(t_info *info)
{
	sem_unlink("death");
	sem_unlink("print");
	sem_unlink("stop");
	sem_unlink("test");
	sem_unlink("forks");
	info->forks = sem_open("forks", O_CREAT, 0600, info->total + 1);
	info->print = sem_open("print", O_CREAT, 0600, 1);
	info->stop = sem_open("stop", O_CREAT, 0600, 1);
	info->death = sem_open("death", O_CREAT, 0600, 1);
	info->test = sem_open("test", O_CREAT, 0600, 1);
}

void	set_philosopher(t_philo **philo, t_info *info)
{
	int	i;

	*philo = malloc (sizeof(t_philo) * info->total);
	i = 0;
	while (i < info->total)
	{
		(*philo)[i].id = i;
		(*philo)[i].eat_stamp = 0;
		(*philo)[i].ate = 0;
		(*philo)[i].info = info;
		i++;
	}
}

void	destory_philosopher(t_philo *philo, t_info *info)
{
	int	i;

	i = 0;
	while (i < info->total)
	{
		kill(philo[i].pid, SIGKILL);
		i++;
	}
	sem_close(info->death);
	sem_close(info->print);
	sem_close(info->stop);
	sem_close(info->forks);
	free(philo);
}

void	fork_philosopher(t_philo *philo, t_info *info)
{
	int	i;

	i = 0;
	while (i < info->total)
	{
		philo[i].pid = fork();
		if (philo[i].pid == 0)
		{
			daily(&philo[i]);
			exit(0);
		}
		i++;
		usleep(100);
	}
}
