/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghyki <sunghyki@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 14:36:11 by sunghyki          #+#    #+#             */
/*   Updated: 2024/05/17 14:36:12 by sunghyki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fork_and_exectue_nested(t_cmd_struct *tcst, int index)
{
	if (tcst->tcmd[index]->pipe_index < tcst->no_of_pipes \
			&& tcst->tcmd[index]->pipe_index != -1)
		close(tcst->tpipe[tcst->tcmd[index]->pipe_index].fd[1]);
}

void	fork_nested(int res, t_cmd_struct *tcst, int index)
{
	char	**env;
	char	*command;

	env = NULL;
	if (res == 1)
	{
		exec_builtin(tcst, index);
		exit(0);
	}
	else if (res == 0)
	{
		if (has_relative_path(tcst->tcmd[index]->arg[0]))
			command = get_exectue_path(\
				get_relative_path_exec(tcst, index), tcst);
		else
			command = get_exectue_path(tcst->tcmd[index]->arg[0], tcst);
		if (command == 0)
			printf("Wrong command\n");
		else
		{
			execve(command, tcst->tcmd[index]->arg, env);
			free(command);
			exit(0);
		}
	}
}

void	free_child(t_cmd_struct *tcst)
{
	free(tcst->tcmd[0]->arg[0]);
	free(tcst->tcmd[0]->arg);
	ft_lstclear(tcst->lst_env, free);
	free(tcst->lst_env);
	free_all(tcst);
}

int	fork_and_execute_andor(t_cmd_struct *tcst, int index)
{
	int		pid;
	int		res;
	int		temp;

	if (handle_res(&res, tcst, index) == 1)
		return (0);
	signal(SIGINT, handle_interrupt_blocked);
	signal(SIGQUIT, handle_interrupt_blocked);
	pid = fork();
	if (pid == 0)
	{
		set_tunnels(tcst, index);
		fork_nested(res, tcst, index);
		temp = tcst->status;
		free_child(tcst);
		exit(temp);
	}
	else if (res != 3 || res != 4)
	{
		handle_parent(tcst);
		fork_and_exectue_nested(tcst, index);
	}
	return (0);
}

int	fork_and_execute(t_cmd_struct *tcst, int index)
{
	int		pid;
	int		res;
	int		temp;

	if (handle_res(&res, tcst, index) == 1)
		return (0);
	signal(SIGINT, handle_interrupt_blocked);
	signal(SIGQUIT, handle_interrupt_blocked);
	pid = fork();
	if (pid == 0)
	{
		set_tunnels(tcst, index);
		fork_nested(res, tcst, index);
		temp = tcst->status;
		free_child(tcst);
		exit(temp);
	}
	else if (res != 3 || res != 4)
		fork_and_exectue_nested(tcst, index);
	return (0);
}
