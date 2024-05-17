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

#include "parse_test.h"

void	copy_string(t_cmd **tcmd, char *src, int len)
{
	(*tcmd)->cmd = malloc (len + 1);
	ft_memcpy((*tcmd)->cmd, src, len);
	(*tcmd)->cmd[len] = 0;
}

void	copy_string_char(char **s, char *src, int len)
{
	char	delim;

	(*s) = malloc (len +1);
	ft_memcpy((*s), src, len);
	(*s)[len] = 0;
	if (src[0] == '?')
	{
		(*s)[0] = '0';
	}
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
