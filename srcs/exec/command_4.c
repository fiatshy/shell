/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonhseo <wonhseo@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 04:58:29 by wonhseo           #+#    #+#             */
/*   Updated: 2024/05/14 05:57:05 by wonhseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	arrange(char *chunk)
{
	size_t	*ict;

	ft_calloc((void **)(&ict), 3, sizeof(size_t));
	mini_assert(ict != NULL, \
		MASSERT "line .");
	while (ict[INDEX] < ft_strlen(chunk))
	{
		if (chunk[ict[INDEX]] == '\'' && ict[TYPE] == OFF)
			ict[TYPE] = SINGLE;
		else if (chunk[ict[INDEX]] == '\'' && ict[TYPE] == SINGLE)
			ict[TYPE] = OFF;
		else if (chunk[ict[INDEX]] == '\"' && ict[TYPE] == OFF)
			ict[TYPE] = DOUBLE;
		else if (chunk[ict[INDEX]] == '\"' && ict[TYPE] == DOUBLE)
			ict[TYPE] = OFF;
		else if (chunk[ict[INDEX]] != '\'' && chunk[ict[INDEX]] != '\"')
			chunk[ict[CONTENT]++] = chunk[ict[INDEX]];
		else if (chunk[ict[INDEX]] == '\"' && ict[TYPE] == SINGLE)
			chunk[ict[CONTENT]++] = '\"';
		else if (chunk[ict[INDEX]] == '\'' && ict[TYPE] == DOUBLE)
			chunk[ict[CONTENT]++] = '\'';
		++ict[INDEX];
	}
	chunk[ict[CONTENT]] = '\0';
	ft_free((void **)(&ict));
}
