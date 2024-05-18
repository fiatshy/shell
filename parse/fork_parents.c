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

#include "parse_test.h"

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
	*res = is_builtin(tcst, index);
	if (*res == 2)
	{
		printf("exit\n");
		free(tcst->tcmd[0]->arg[0]);
		free(tcst->tcmd[0]->arg);
		free_all(tcst);
		exit(0);
	}
	else if (*res == 3)
	{
		ft_cd(tcst, index);
		return (1);
	}
	return (handle_res_nested(res, tcst, index));
}

void	handle_parent(t_cmd_struct *tcst, int index)
{
	waitpid(0, &tcst->status, 0);
	tcst->status = WEXITSTATUS(tcst->status);
	fork_and_exectue_nested(tcst, index);
}
