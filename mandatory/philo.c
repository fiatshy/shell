/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghyki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 08:21:24 by sunghyki          #+#    #+#             */
/*   Updated: 2024/04/22 08:21:26 by sunghyki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_info	info;
	t_philo	*philo;

	if (ac == 5 || ac == 6)
	{
		init_info(&info, ac, av);
		init_mutex(&info);
		init_philo(&info, &philo);
		run_thread(&info, philo);
		pthread_mutex_lock(info.stop);
		free_all(&info, philo);
	}
	else
		printf("You must enter 4 plus 1 optinal arguments.");
	return (0);
}
