/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghyki <sunghyki@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 09:19:50 by sunghyki          #+#    #+#             */
/*   Updated: 2024/05/07 09:19:52 by sunghyki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_pipe_head(t_cmd_struct *tcst)
{
	int	i;

	i = 0;
	while (i < tcst->no_of_pipes)
	{
		close(tcst->tpipe[i].fd[0]);
		if (i != 0)
			close(tcst->tpipe[i].fd[1]);
		i++;
	}
	dup2(tcst->tpipe[0].fd[1], 1);
	close(tcst->tpipe[0].fd[1]);
}

void	set_pipe_body(t_cmd_struct *tcst, int cmd_index)
{
	int	i;

	i = 0;
	while (i < tcst->no_of_pipes)
	{
		if (i != cmd_index - 1)
			close(tcst->tpipe[i].fd[0]);
		if (i != cmd_index)
			close(tcst->tpipe[i].fd[1]);
		i++;
	}
	dup2(tcst->tpipe[cmd_index - 1].fd[0], 0);
	dup2(tcst->tpipe[cmd_index].fd[1], 1);
	close(tcst->tpipe[cmd_index - 1].fd[0]);
	close(tcst->tpipe[cmd_index].fd[1]);
}

void	set_pipe_tail(t_cmd_struct *tcst)
{
	int	i;

	i = 0;
	while (i < tcst->no_of_pipes)
	{
		if (i != tcst->no_of_pipes - 1)
			close(tcst->tpipe[i].fd[0]);
		close(tcst->tpipe[i].fd[1]);
		i++;
	}
	dup2(tcst->tpipe[tcst->no_of_pipes - 1].fd[0], 0);
	close(tcst->tpipe[tcst->no_of_pipes - 1].fd[0]);
}
