/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghyki <sunghyki@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 14:36:08 by sunghyki          #+#    #+#             */
/*   Updated: 2024/05/17 14:36:09 by sunghyki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_test.h"

int	is_builtin(t_cmd_struct *tcst, int index)
{
	if (ft_strncmp("echo", tcst->tcmd[index]->arg[0], 4) == 0)
		return (1);
	else if (ft_strncmp("exit", tcst->tcmd[index]->arg[0], 4) == 0)
		return (2);
	else if (ft_strncmp("$?", tcst->tcmd[index]->arg[0], 2) == 0)
		return (6);
	else if (ft_strncmp("pwd", tcst->tcmd[index]->arg[0], 3) == 0)
		return (1);
	else if (ft_strncmp("cd", tcst->tcmd[index]->arg[0], 3) == 0)
		return (3);
	else if (ft_strncmp("env", tcst->tcmd[index]->arg[0], 3) == 0)
		return (1);
	else if (ft_strncmp("export", tcst->tcmd[index]->arg[0], 6) == 0)
		return (4);
	else if (ft_strncmp("unset", tcst->tcmd[index]->arg[0], 5) == 0)
		return (5);
	return (0);
}

int	exec_builtin(t_cmd_struct *tcst, int index)
{
	if (ft_strncmp("echo", tcst->tcmd[index]->arg[0], 4) == 0)
		ft_echo(tcst, index);
	else if (ft_strncmp("exit", tcst->tcmd[index]->arg[0], 4) == 0)
		ft_exit();
	else if (ft_strncmp("$?", tcst->tcmd[index]->arg[0], 2) == 0)
		ft_status(tcst);
	else if (ft_strncmp("pwd", tcst->tcmd[index]->arg[0], 3) == 0)
		ft_pwd();
	else if (ft_strncmp("cd", tcst->tcmd[index]->arg[0], 3) == 0)
		ft_cd(tcst, index);
	else if (ft_strncmp("env", tcst->tcmd[index]->arg[0], 3) == 0)
		ft_env(tcst);
	else if (ft_strncmp("export", tcst->tcmd[index]->arg[0], 6) == 0)
		ft_export(tcst, index);
	else if (ft_strncmp("unset", tcst->tcmd[index]->arg[0], 5) == 0)
		ft_unset(tcst, index);
	return (1);
}
