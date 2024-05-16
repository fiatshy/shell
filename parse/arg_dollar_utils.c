/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_dollar_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghyki <sunghyki@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:53:18 by sunghyki          #+#    #+#             */
/*   Updated: 2024/05/16 17:53:19 by sunghyki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_test.h"

int	have_quote(char *s)
{
	while (*s)
	{
		if (*s == '\'' || *s == '"')
			return (1);
		s++;
	}
	return (0);
}

int	have_dollar_nonzero(char *s)
{
	while (*s)
	{
		if (*s == '$')
			return (1);
		s++;
	}
	return (0);
}

void	free_noquote_dollar(char **split_env)
{
	free(split_env[0]);
	free(split_env[1]);
	free(split_env);
}

void	noquote_nested(char **s, t_list *temp)
{
	char	**split_env;

	split_env = ft_split(temp->content, '=');
	free(*s);
	*s = malloc (ft_strlen(split_env[1]) + 1);
	ft_memcpy(*s, split_env[1], ft_strlen(split_env[1]));
	(*s)[ft_strlen(split_env[1])] = 0;
	free_noquote_dollar(split_env);
}

void	make_blank_string(char **s)
{
	free(*s);
	(*s) = malloc (2);
	(*s)[0] = ' ';
	(*s)[1] = 0;
}
