/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghyki <sunghyki@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 09:21:26 by sunghyki          #+#    #+#             */
/*   Updated: 2024/05/07 09:21:28 by sunghyki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	copy_string(t_cmd **tcmd, char *src, int len)
{
	(*tcmd)->cmd = malloc (len + 1);
	ft_memcpy((*tcmd)->cmd, src, len);
	(*tcmd)->cmd[len] = 0;
}

void	copy_string_char(t_cmd_struct *tcst, char **s, char *src, int len)
{
	char	delim;

	(*s) = malloc (len +1);
	ft_memcpy((*s), src, len);
	(*s)[len] = 0;
	if (src[0] == '?' && ft_strncmp("expr", tcst->tcmd[0]->arg[0], 4) == 0)
		*s = ft_itoa(tcst->status);
	if (((*s)[0] == '\'') || ((*s)[0] == '\"'))
	{
		delim = (*s)[0];
		if ((*s)[len - 1] == delim)
			*s = ft_strtrim(*s, &delim);
	}
}

void	check_redirection(char **s, bool *quote, int *count)
{
	if ((**s == '"' || **s == '\'') && !(*quote))
		*quote = true;
	else if ((**s == '"' || **s == '\'') && *quote)
		*quote = false;
	if (!(*quote))
	{
		if (ft_strncmp(*s, ">>", 2) == 0)
		{
			(*s)++;
			(*count)++;
		}
		else if (ft_strncmp(*s, "<<", 2) == 0)
		{
			(*s)++;
			(*count)++;
		}
		else if (ft_strncmp(*s, ">", 1) == 0)
			(*count)++;
		else if (ft_strncmp(*s, "<", 1) == 0)
			(*count)++;
	}
}

void	main_init(int *status, t_list ***lst_env)
{
	*status = 0;
	*lst_env = malloc (sizeof(t_list *));
	init_env(*lst_env);
	signal(SIGINT, handle_interrupt);
	signal(SIGQUIT, SIG_IGN);
}

void	main_check_pipe(t_cmd_struct *tcst)
{
	if (tcst->no_of_pipes <= 5)
	{
		init_pipe(tcst);
		prepare_execute(tcst);
		signal(SIGINT, handle_interrupt);
		signal(SIGQUIT, SIG_IGN);
	}
	else
		printf("too many pipes\n");
}
