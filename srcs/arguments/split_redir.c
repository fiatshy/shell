/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghyki <sunghyki@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 13:12:05 by sunghyki          #+#    #+#             */
/*   Updated: 2024/05/28 13:12:06 by sunghyki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_redirect_kind(char *s)
{
	if (ft_strncmp(s, ">>", 2) == 0)
	{
		return (2);
	}
	else if (ft_strncmp(s, "<<", 2) == 0)
	{
		return (2);
	}
	else if (ft_strncmp(s, ">", 1) == 0)
	{
		return (1);
	}
	else if (ft_strncmp(s, "<", 1) == 0)
	{
		return (1);
	}
	return (0);
}

int	check_attached_redir(char *s)
{
	int	n;

	while (*s)
	{
		n = check_redirect_kind(s);
		if (n && *(s + n) != 0)
		{
			return (1);
		}
		s++;
	}
	return (0);
}

void	split_redir_front_token(char *s, char **split_second)
{
	int	i;

	*split_second = malloc (3);
	ft_memset(*split_second, 0, 3);
	i = 0;
	while (*s)
	{
		if (*s != '<' && *s != '>')
			break ;
		(*split_second)[i++] = *s;
		s++;
	}
}

void	split_redir_end_token(char *s, char **split_second)
{
	int	i;

	*split_second = malloc (20);
	ft_memset(*split_second, 0, 20);
	i = 0;
	while (*s)
	{
		if (*s != '<' && *s != '>')
			break ;
		s++;
	}
	i = 0;
	while (*s)
	{
		(*split_second)[i++] = *s;
		s++;
	}
}
