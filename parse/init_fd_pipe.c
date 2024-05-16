/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fd_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghyki <sunghyki@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:54:00 by sunghyki          #+#    #+#             */
/*   Updated: 2024/05/16 17:54:03 by sunghyki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_test.h"

void	init_fds(t_cmd_struct *tcst)
{
	int	i;

	i = 0;
	while (i < 10)
	{
		tcst->tfd[i].append = -1;
		tcst->tfd[i].read = -1;
		tcst->tfd[i].tmp = -1;
		tcst->tfd[i].write = -1;
		i++;
	}
}

void	init_pipe(t_cmd_struct *tcst)
{
	int	i;

	i = 0;
	while (i < tcst->no_of_pipes)
	{
		pipe(tcst->tpipe[i].fd);
		i++;
	}
}

void	nested_pipe_index(t_cmd_struct *tcst, int i)
{
	if (ft_strncmp(tcst->tcmd[i - 1]->next_delimiter, "||", 2) == 0 && \
			tcst->tcmd[i - 1]->pipe_index != -1)
		tcst->tcmd[i]->pipe_index = -1;
	else if (ft_strncmp(tcst->tcmd[i]->next_delimiter, "|", 1) == 0 || \
			tcst->tcmd[i - 1]->pipe_index != -1)
	{
		if (i != 0)
			tcst->tcmd[i]->pipe_index = tcst->tcmd[i - 1]->pipe_index + 1;
		else if (i == 0)
			tcst->tcmd[i]->pipe_index = 0;
	}
	else if (ft_strncmp(tcst->tcmd[i - 1]->next_delimiter, "&&", 2) == 0 && \
			tcst->tcmd[i - 1]->pipe_index != -1)
	{
		tcst->tcmd[i]->pipe_index = -1;
	}
}

void	set_pipe_index(t_cmd_struct *tcst, int i)
{
	tcst->tcmd[i]->pipe_index = -1;
	if (i != 0)
		nested_pipe_index(tcst, i);
	else if (i == 0)
	{
		if (ft_strncmp(tcst->tcmd[i]->next_delimiter, "|", 2) == 0)
			tcst->tcmd[i]->pipe_index = 0;
	}
}
