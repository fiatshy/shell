/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_redirect_nested.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghyki <sunghyki@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 14:36:17 by sunghyki          #+#    #+#             */
/*   Updated: 2024/05/17 14:36:18 by sunghyki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirect_parents(t_cmd_struct *tcst, int index)
{
	waitpid(0, &tcst->status, 0);
	close_fds(tcst);
	if (index < tcst->no_of_pipes)
		close(tcst->tpipe[index].fd[1]);
}

void	execute_redirection(t_cmd_struct *tcst, int index)
{
	int		pid;
	char	**envs;
	char	*command;

	pid = fork();
	envs = NULL;
	if (pid == 0)
	{
		init_dup2(tcst);
		set_tunnel_redirect(tcst, index);
		command = make_bin(tcst);
		if (command == 0)
			printf("Wrong command.");
		else
			execve(make_bin(tcst), tcst->trst->args, envs);
		return ;
	}
	else
		redirect_parents(tcst, index);
	close_fds(tcst);
	free_redirect_all(tcst);
}

int	get_args_length(char **s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (i == 0)
		{
			if (ft_strncmp(s[i], ">", 1) && ft_strncmp(s[i], "<", 1))
				count++;
		}
		else
		{
			if (ft_strncmp(s[i - 1], ">", 1) && ft_strncmp(s[i - 1], "<", 1))
				if (ft_strncmp(s[i], ">", 1) && ft_strncmp(s[i], "<", 1))
					count++;
		}
		i++;
	}
	return (count);
}

int	handle_redirection_nested(t_cmd_struct *tcst, int j)
{
	t_var	nested;
	int		index;
	char	**split_first;

	while (tcst->trst->split_redirection[j])
	{
		split_first = ft_split(tcst->trst->split_redirection[j++], ' ');
		tcst->trst->split_again = malloc (sizeof(char *) \
			* (count_malloc_length(split_first) + 1));
		move_split(split_first, tcst);
		nested.k = 0;
		index = 0;
		nested.length = get_args_length(tcst->trst->split_again);
		tcst->trst->args = malloc (sizeof(char *) * (nested.length + 1));
		tcst->trst->args[nested.length] = 0;
		if (open(tcst->trst->split_again[1], O_RDONLY) == -1 \
			&& tcst->trst->split_again[nested.k][0] == '<' && \
			tcst->trst->split_again[nested.k][1] != '<')
			return (-1);
		nested_nested(nested, tcst, &index);
	}
	free_redirection(tcst, j);
	return (0);
}

int	handle_redirection(t_cmd_struct *tcst, int i)
{
	int		j;
	char	*s;

	tcst->trst = malloc (sizeof(t_red_struct));
	tcst->trst->split_redirection = ft_split(tcst->tcmd[i]->cmd, '=');
	s = tcst->trst->split_redirection[0];
	(void) s;
	//if (check_wrong_redirection(s) == -1)
	//	return (-1);
	j = 0;
	tcst->trst->args = malloc (sizeof(char *) * 2);
	if (handle_redirection_nested(tcst, j) == -1)
		return (0);
	execute_redirection(tcst, i);
	return (0);
}
