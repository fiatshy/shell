/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghyki <sunghyki@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 09:21:08 by sunghyki          #+#    #+#             */
/*   Updated: 2024/05/07 09:21:11 by sunghyki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "parse_test.h"

void	init_tcst(t_cmd_struct **tcst, char *s, int status)
{
	int		i;

	(*tcst) = malloc (sizeof(t_cmd_struct));
	(*tcst)->n = get_no_of_command(s);
	if ((*tcst)->n == 0)
		(*tcst)->n = 1;
	(*tcst)->tcmd = malloc (sizeof(t_cmd));
	i = 0;
	while (i < (*tcst)->n)
	{
		(*tcst)->tcmd[i] = malloc (sizeof(t_cmd));
		i++;
	}
	(*tcst)->status = status;
	(*tcst)->tfd_index[0] = 0;
	(*tcst)->tfd_index[1] = 0;
	(*tcst)->tfd_index[2] = 0;
	(*tcst)->tfd_index[3] = 0;
	init_fds(*tcst);
}

void	free_init_tcmd(char **split, char *trim_str)
{
	free(trim_str);
	free(split[0]);
	free(split[1]);
	free(split);
}

void	init_tcmd_set_openclose(t_cmd_struct *tcst, char **split, int i)
{
	if (has_open_parenthesis(split[0]))
	{
		tcst->tcmd[i]->open = true;
		tcst->open = 1;
	}
	if (has_close_parenthesis(split[0]))
		tcst->tcmd[i]->close = true;
}

void	init_tcmd(t_cmd_struct *tcst)
{
	int		i;
	char	**split;
	char	*temp;
	char	*trim_str;

	i = 0;
	copy_string_char(&temp, tcst->s, ft_strlen(tcst->s));
	free(tcst->s);
	while (i < tcst->n)
	{
		tcst->tcmd[i]->next_delimiter = get_first_delimiter(temp);
		set_pipe_index(tcst, i);
		split = ft_split_first(temp);
		init_tcmd_set_openclose(tcst, split, i);
		trim_str = ft_strtrim(split[0], " ()");
		copy_string(&tcst->tcmd[i], trim_str, ft_strlen(trim_str));
		if (temp != NULL)
			free(temp);
		if (split[1] != NULL)
			copy_string_char(&temp, split[1], ft_strlen(split[1]));
		free_init_tcmd(split, trim_str);
		i++;
	}
}
