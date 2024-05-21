/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghyki <sunghyki@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 14:36:02 by sunghyki          #+#    #+#             */
/*   Updated: 2024/05/17 14:36:05 by sunghyki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(t_cmd_struct *tcst, int index)
{
	int		i;

	if (ft_strncmp("-n", tcst->tcmd[index]->arg[1], 2) == 0)
	{
		i = 2;
		while (tcst->tcmd[index]->arg[i])
		{
			if (i != 2)
				printf(" ");
			trim(tcst, index, i);
			i++;
		}
	}
	else
	{
		i = 1;
		while (tcst->tcmd[index]->arg[i])
		{
			if (i != 1)
				printf(" ");
			trim(tcst, index, i);
			i++;
		}
		printf("\n");
	}
}

void	ft_exit(void)
{
	printf("exit\n");
}

void	ft_status(t_cmd_struct *tcst)
{
	printf("%d\n", tcst->status);
}

void	ft_pwd(void)
{
	char	buf[255];

	getcwd(buf, 255);
	printf("%s\n", buf);
}
