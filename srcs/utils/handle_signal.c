/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghyki <sunghyki@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 14:36:34 by sunghyki          #+#    #+#             */
/*   Updated: 2024/05/17 14:36:36 by sunghyki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_interrupt(int signo)
{
	(void) signo;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_interrupt_blocked(int signo)
{
	(void) signo;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
}

int	check_if_ctrl_d(char *s)
{
	while (*s)
	{
		if (*s == '\n')
			return (0);
		s++;
	}
	return (1);
}
