/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_question_set.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghyki <sunghyki@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:53:19 by sunghyki          #+#    #+#             */
/*   Updated: 2024/05/16 17:53:21 by sunghyki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	make_question_mark(char **s)
{
	free(*s);
	(*s) = malloc (2);
	(*s)[0] = '?';
	(*s)[1] = 0;
}

int	handle_question(char **s)
{
	(*s) = ft_strtrim((*s), "$");
	if ((*s)[0] == '?')
	{
		make_question_mark(s);
		return (1);
	}
	return (0);
}

void	handle_noquote_dollar(char **s, t_cmd_struct *tcst)
{
	t_list	*temp;
	int		flag;

	flag = true;
	temp = *tcst->lst_env;
	if (handle_question(s) == 1)
		return ;
	while (temp)
	{
		if (ft_strncmp(temp->content, *s, ft_strlen(*s)) == 0)
		{
			flag = false;
			noquote_nested(s, temp);
			break ;
		}
		temp = temp->next;
	}
	if (flag)
		make_blank_string(s);
}

int	has_expr(char *s)
{
	if (ft_strncmp("expr", s, 4) == 0)
		return (1);
	return (0);
}
