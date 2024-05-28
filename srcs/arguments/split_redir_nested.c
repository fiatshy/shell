/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_redir_nested.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghyki <sunghyki@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 13:12:10 by sunghyki          #+#    #+#             */
/*   Updated: 2024/05/28 13:12:12 by sunghyki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_malloc_length(char **split_first)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (split_first[i])
	{
		if (check_attached_redir(split_first[i]) == 1)
			count++;
		i++;
	}
	return (i + count);
}

void	move_split(char **split_first, t_cmd_struct *tcst)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (split_first[i])
	{
		if (check_attached_redir(split_first[i]) == 1)
		{
			split_redir_front_token(split_first[i], \
				&tcst->trst->split_again[j]);
			j++;
			split_redir_end_token(split_first[i], \
				&tcst->trst->split_again[j]);
			j++;
		}
		else
		{
			tcst->trst->split_again[j++] = split_first[i];
		}
		i++;
	}
}

void	nested_nested(t_var nested, t_cmd_struct *tcst, int *index)
{	
	while (tcst->trst->split_again[nested.k])
	{
		handle_again(tcst, nested.k, index);
		nested.k++;
	}
	free_again(tcst, nested.k);
}
