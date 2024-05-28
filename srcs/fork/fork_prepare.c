/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_prepare.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghyki <sunghyki@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 14:36:14 by sunghyki          #+#    #+#             */
/*   Updated: 2024/05/17 14:36:15 by sunghyki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_wrong_redirection(char *s)
{
	while (*s)
	{
		if (*s == '<' || *s == '>')
		{
			if (*(s + 1) == '<' || *(s + 1) == '>')
			{
				if (*(s + 2) != ' ')
				{
					printf("Wrong Command: \
						redirect commands needs space between arguments\n");
					return (-1);
				}
			}
			else
			{
				if (*(s + 1) != ' ')
				{
					printf("Wrong Command: \
						redirect commands needs space between arguments\n");
					return (-1);
				}
			}
		}
		s++;
	}
	return (0);
}

int	prepare_execute_nested_andor(t_cmd_struct *tcst, \
	int i, int proceed, int cont)
{
	int	no_of_redirection;

	while (i < tcst->n)
	{
		no_of_redirection = get_no_of_redirection(tcst->tcmd[i]);
		if (no_of_redirection == 0)
		{
			if (set_arguments(tcst->tcmd[i], tcst) == -1)
				return (0);
			cont = check_grouping(tcst, &i, &proceed);
			if (cont == -1)
				continue ;
			if (proceed)
				fork_and_execute_andor(tcst, i);
			free_after_exectue(tcst, i, &proceed);
		}
		else
		{
			if (handle_redirection(tcst, i) == -1)
				return (0);
		}
		i++;
	}
	return (0);
}

int	wait_for_child(t_cmd_struct *tcst)
{
	int	i;
	int	temp;

	i = -1;
	while (++i < tcst->no_of_pipes)
	{
		close(tcst->tpipe[tcst->tcmd[i]->pipe_index].fd[0]);
		close(tcst->tpipe[tcst->tcmd[i]->pipe_index].fd[1]);
	}
	i = -1;
	temp = tcst->status;
	while (++i < tcst->n)
		handle_parent(tcst);
	if (tcst->builtin == 0)
		return (tcst->status);
	else if (tcst->builtin == 1)
		return (temp);
	return (0);
}

int	prepare_execute_nested(t_cmd_struct *tcst, int i, int proceed, int cont)
{
	int	no_of_redirection;

	while (i < tcst->n)
	{
		no_of_redirection = get_no_of_redirection(tcst->tcmd[i]);
		if (no_of_redirection == 0)
		{
			if (set_arguments(tcst->tcmd[i], tcst) == -1)
				return (0);
			cont = check_grouping(tcst, &i, &proceed);
			if (cont == -1)
				continue ;
			if (proceed)
				fork_and_execute(tcst, i);
			free_after_exectue(tcst, i, &proceed);
		}
		else
		{
			if (handle_redirection(tcst, i) == -1)
				return (0);
		}
		i++;
	}
	tcst->status = wait_for_child(tcst);
	return (0);
}

int	prepare_execute(t_cmd_struct *tcst)
{
	int		i;
	int		proceed;
	int		cont;

	i = 0;
	cont = 0;
	proceed = 1;
	if (has_andor(tcst) == 1)
	{
		prepare_execute_nested_andor(tcst, i, proceed, cont);
		return (0);
	}
	if (prepare_execute_nested(tcst, i, proceed, cont) == 0)
		return (0);
	return (0);
}
