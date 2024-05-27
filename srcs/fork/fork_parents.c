/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_parents.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghyki <sunghyki@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 14:36:13 by sunghyki          #+#    #+#             */
/*   Updated: 2024/05/17 14:36:14 by sunghyki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_res_nested(int *res, t_cmd_struct *tcst, int index)
{
	if (*res == 4)
	{
		if (tcst->tcmd[index]->arg[1] == NULL)
		{
			show_env_list(tcst->lst_env);
			return (1);
		}
		ft_export(tcst, index);
		return (1);
	}
	else if (*res == 5)
	{
		if (tcst->tcmd[index]->arg[1] == NULL)
			printf("not enough arguments\n");
		else
			ft_unset(tcst, index);
		return (1);
	}
	else if (*res == 6)
	{
		ft_status(tcst);
		return (1);
	}
	return (0);
}

int	handle_res(int *res, t_cmd_struct *tcst, int index)
{
	int	length;

	*res = is_builtin(tcst, index);
	if (*res == 1)
	{
		ft_echo(tcst, index);
		return (1);
	}
	if (*res == 2)
	{
		length = 0;
		while (tcst->tcmd[0]->arg[length])
			length++;
		if (length > 2)
			printf("too many variables\n");	
		else
		{
			printf("exit\n");
			free(tcst->tcmd[0]->arg[0]);
			free(tcst->tcmd[0]->arg);
			ft_lstclear(tcst->lst_env, free);
			free(tcst->lst_env);
			free_all(tcst);
			exit(0);
		}
	}
	else if (*res == 3)
	{
		ft_cd(tcst, index);
		return (1);
	}
	return (handle_res_nested(res, tcst, index));
}

void	handle_parent(t_cmd_struct *tcst)
{
	waitpid(0, &tcst->status, 0);
	tcst->status = WEXITSTATUS(tcst->status);
}

void	delim_nested_loop(t_cmd_struct *tcst, int k)
{
	char	*temp;

	signal(SIGINT, heredoc_signal);
	while (1)
	{
		temp = readline("heredoc >> ");
		if (ft_strncmp(temp, tcst->trst->split_again[k + 1], \
			ft_strlen(temp)) == 0)
			break ;
		else
		{
			write(tcst->tfd[tcst->tfd_index[0]].tmp, temp, ft_strlen(temp));
			write(tcst->tfd[tcst->tfd_index[0]].tmp, "\n", 1);
		}
	}
}
