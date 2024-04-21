/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghyki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:19:39 by sunghyki          #+#    #+#             */
/*   Updated: 2024/04/19 15:19:41 by sunghyki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int ac, char **av)
{
	t_info	info;
	t_philo	*philo;
	int		i;

	if (ac == 5 || ac == 6)
		set_parameter(ac, av, &info);
	else
		printf("You must enter 4 plus 1 optional arguments.\n");
	set_semaphore(&info);
	set_philosopher(&philo, &info);
	sem_wait(info.stop);
	fork_philosopher(philo, &info);
	i = 0;
	while (i < info.total)
	{
		sem_wait(info.stop);
		i++;
	}
	destory_philosopher(philo, &info);
	return (0);
}
