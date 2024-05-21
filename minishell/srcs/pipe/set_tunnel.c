/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_tunnel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghyki <sunghyki@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 14:36:48 by sunghyki          #+#    #+#             */
/*   Updated: 2024/05/17 14:36:49 by sunghyki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_tunnels(t_cmd_struct *tcst, int index)
{
	if (tcst->tcmd[index]->pipe_index != -1)
	{
		if (tcst->tcmd[index]->pipe_index == 0)
			set_pipe_head(tcst);
		else if (tcst->tcmd[index]->pipe_index == tcst->no_of_pipes)
			set_pipe_tail(tcst);
		else
			set_pipe_body(tcst, tcst->tcmd[index]->pipe_index);
	}
}

void	init_dup2(t_cmd_struct *tcst)
{
	int	i;

	i = 0;
	while (i < 10)
	{
		if (tcst->tfd[i].write > 0)
			dup2(tcst->tfd[i].write, 1);
		if (tcst->tfd[i].append > 0)
			dup2(tcst->tfd[i].append, 1);
		if (tcst->tfd[i].tmp > 0)
			dup2(tcst->tfd[i].tmp, 0);
		if (tcst->tfd[i].read > 0)
			dup2(tcst->tfd[i].read, 0);
		i++;
	}
}

void	close_fds(t_cmd_struct *tcst)
{
	int	i;

	i = 0;
	while (i < 10)
	{
		if (tcst->tfd[i].write > 0)
			close(tcst->tfd[i].write);
		if (tcst->tfd[i].append > 0)
			close(tcst->tfd[i].append);
		if (tcst->tfd[i].tmp > 0)
			close(tcst->tfd[i].tmp);
		if (tcst->tfd[i].read > 0)
			close(tcst->tfd[i].read);
		i++;
	}
}

char	*make_bin(t_cmd_struct *tcst)
{
	char	*command;

	command = get_exectue_path(tcst->trst->args[0], tcst);
	return (command);
}

void	set_tunnel_redirect(t_cmd_struct *tcst, int index)
{
	if (tcst->tcmd[index]->pipe_index != -1)
	{
		if (tcst->tcmd[index]->pipe_index == 0)
			set_pipe_head(tcst);
		else if (tcst->tcmd[index]->pipe_index == tcst->no_of_pipes)
			set_pipe_tail(tcst);
		else
			set_pipe_body(tcst, tcst->tcmd[index]->pipe_index);
	}
}
