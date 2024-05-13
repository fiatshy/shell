/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonhseo <wonhseo@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 05:01:48 by wonhseo           #+#    #+#             */
/*   Updated: 2024/05/14 06:46:15 by wonhseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	set_rl(char *in, char *out, int fd, bool newline)
{
	if (in != NULL)
	{
		ft_putstr(in, fd);
		ft_putstr(": ", fd);
	}
	if (out != NULL)
		ft_putstr(out, fd);
	ft_putendl("", fd);
	if (newline)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	return (true);
}

void	customized(int sig)
{
	(void)sig;
	set_rl(NULL, NULL, STDOUT_FILENO, true);
}

void	set_signal(void (*action1)(int), void (*action2)(int))
{
	signal(SIGINT, action1);
	signal(SIGQUIT, action2);
}
