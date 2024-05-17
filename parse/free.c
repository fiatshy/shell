/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghyki <sunghyki@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 14:36:18 by sunghyki          #+#    #+#             */
/*   Updated: 2024/05/17 14:36:19 by sunghyki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_test.h"

void	free_after_exectue(t_cmd_struct *tcst, int i, int *proceed)
{
	int	j;

	j = 0;
	if (i < tcst->n)
	{
		while (tcst->tcmd[i]->arg[j])
		{
			free(tcst->tcmd[i]->arg[j]);
			j++;
		}
		free(tcst->tcmd[i]->arg);
		*proceed = true;
	}
}

void	free_again(t_cmd_struct *tcst, int k)
{
	int	i;

	i = 0;
	while (i < k)
	{
		free(tcst->trst->split_again[i]);
		i++;
	}
	free(tcst->trst->split_again);
}

int	free_redirect_all(t_cmd_struct *tcst)
{
	int	l;

	l = 0;
	while (l < 2)
	{
		free(tcst->trst->args[l]);
		l++;
	}
	free(tcst->trst->args);
	free(tcst->trst);
	return (0);
}

void	free_redirection(t_cmd_struct *tcst, int j)
{
	int	l;

	l = 0;
	while (l < j)
	{
		free(tcst->trst->split_redirection[l]);
		l++;
	}
	free(tcst->trst->split_redirection);
}

int	free_all(t_cmd_struct *tcst)
{
	int	i;
	int	temp;

	i = 0;
	temp = tcst->status;
	while (i < tcst->n)
	{
		free(tcst->tcmd[i]->cmd);
		free(tcst->tcmd[i]);
		i++;
	}
	free(tcst->tcmd);
	free(tcst);
	return (temp);
}
