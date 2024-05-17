/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghyki <sunghyki@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 14:36:16 by sunghyki          #+#    #+#             */
/*   Updated: 2024/05/17 14:36:17 by sunghyki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_test.h"

void	set_redirect_args(t_cmd_struct *tcst, int *index, int k)
{
	if (k == 0 && ft_strncmp(tcst->trst->split_again[k], "<", 1) \
			&& ft_strncmp(tcst->trst->split_again[k], ">", 1))
	{
		tcst->trst->args[*index] = malloc \
			(sizeof(ft_strlen(tcst->trst->split_again[k]) + 1));
		ft_memcpy(tcst->trst->args[*index], \
			tcst->trst->split_again[k], \
				ft_strlen(tcst->trst->split_again[k]) + 1);
		*index += 1;
	}
	else if (k != 0 && ft_strncmp(tcst->trst->split_again[k - 1], "<", 1) \
			&& ft_strncmp(tcst->trst->split_again[k - 1], ">", 1))
	{
		if (ft_strncmp(tcst->trst->split_again[k], "<", 1) \
			&& ft_strncmp(tcst->trst->split_again[k], ">", 1))
		{
			tcst->trst->args[*index] = malloc \
			(sizeof(ft_strlen(tcst->trst->split_again[k]) + 1));
			ft_memcpy(tcst->trst->args[*index], \
			tcst->trst->split_again[k], \
			ft_strlen(tcst->trst->split_again[k]) + 1);
			*index += 1;
		}
	}
}

void	handle_redirect_delim_nested(t_cmd_struct *tcst)
{
	close(tcst->tfd[tcst->tfd_index[0]].tmp);
	tcst->tfd[tcst->tfd_index[0]].tmp = open("tmp", O_RDWR);
	tcst->tfd_index[0] += 1;
}

void	handle_redirect_delim(t_cmd_struct *tcst, int k)
{
	int		r;
	char	temp[100];

	if (ft_strncmp(tcst->trst->split_again[k], "<<", 2) == 0)
	{
		tcst->tfd[tcst->tfd_index[0]].tmp = \
			open("tmp", O_CREAT | O_RDWR | O_TRUNC, 0777);
		while (1)
		{
			ft_memset(temp, 0, 100);
			r = read(0, temp, 100);
			if (ft_strncmp(temp, tcst->trst->split_again[k + 1], \
				ft_strlen(temp) - 1) == 0)
				break ;
			else
				write(tcst->tfd[tcst->tfd_index[0]].tmp, temp, r);
		}
		handle_redirect_delim_nested(tcst);
	}
	else if (ft_strncmp(tcst->trst->split_again[k], "<", 1) == 0)
	{
		tcst->tfd[tcst->tfd_index[1]].read = \
			open(tcst->trst->split_again[k + 1], O_RDONLY, 0777);
		tcst->tfd_index[1] += 1;
	}
}

void	handle_redirect_output(t_cmd_struct *tcst, int k)
{
	struct stat	buf;

	if (ft_strncmp(tcst->trst->split_again[k], ">>", 2) == 0)
	{
		tcst->tfd[tcst->tfd_index[2]].append = \
			open(tcst->trst->split_again[k + 1], \
				O_WRONLY | O_CREAT | O_APPEND, 0777);
		tcst->tfd_index[2] += 1;
	}
	else if (ft_strncmp(tcst->trst->split_again[k], ">", 1) == 0)
	{
		if (stat(tcst->trst->split_again[k + 1], &buf) == 0)
			remove(tcst->trst->split_again[k + 1]);
		tcst->tfd[tcst->tfd_index[3]].write = \
			open(tcst->trst->split_again[k + 1], \
				O_WRONLY | O_CREAT, 0777);
		tcst->tfd_index[3] += 1;
	}
}

void	handle_again(t_cmd_struct *tcst, int k, int *index)
{
	set_redirect_args(tcst, index, k);
	handle_redirect_delim(tcst, k);
	handle_redirect_output(tcst, k);
}
