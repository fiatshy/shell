/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_dollar_environ.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghyki <sunghyki@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:53:14 by sunghyki          #+#    #+#             */
/*   Updated: 2024/05/16 17:53:16 by sunghyki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	split_envirion_nested(char *string, int idx, char temp[4][100])
{
	int	cnt;

	cnt = 0;
	while (*(string + idx))
	{
		if (*(string + idx) == '\'' || \
			*(string + idx) == '\"' || *(string + idx) == ' ')
			break ;
		temp[1][cnt] = *(string + idx);
		idx++;
		cnt++;
	}
	temp[1][cnt] = 0;
	cnt = 0;
	while (*(string + idx))
	{
		temp[2][cnt] = *(string + idx);
		idx++;
		cnt++;
	}
	temp[2][cnt] = 0;
	temp[3][0] = 0;
}

void	split_environ(char *string, char temp[4][100])
{
	int		idx;

	idx = 0;
	ft_memset(temp[0], 0, 100);
	while (*(string + idx))
	{
		if (*(string + idx) == '$')
		{
			break ;
		}
		temp[0][idx] = *(string + idx);
		idx++;
	}
	temp[0][idx] = 0;
	idx++;
	split_envirion_nested(string, idx, temp);
}

void	free_env_input(char **split_env_input)
{
	int	j;

	j = 0;
	while (split_env_input[j])
	{
		free(split_env_input[j]);
		j++;
	}
	free(split_env_input);
}

void	set_redirect_nested(t_cmd_struct *tcst, int *index, int k)
{
	char	*temp_str;
	char	*delim;

	delim = what_quotes_arg(tcst->trst->split_again[k]);
	if (delim != NULL)
		temp_str = ft_strtrim(tcst->trst->split_again[k], delim);
	else
		temp_str = tcst->trst->split_again[k];
	tcst->trst->args[*index] = malloc \
	(sizeof(ft_strlen(temp_str) + 1));
	ft_memcpy(tcst->trst->args[*index], \
	temp_str, \
	ft_strlen(temp_str) + 1);
}
