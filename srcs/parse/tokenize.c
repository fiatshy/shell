/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonhseo <wonhseo@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 05:01:08 by wonhseo           #+#    #+#             */
/*   Updated: 2024/05/14 06:45:44 by wonhseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*tokenize_internal(char *input, char *begin, char *end, t_lst **chunks)
{
	char	*token;
	t_lst	*temp;

	token = ft_substr(input, begin - input, end - begin + 1);
	temp = ft_lstnew(token);
	mini_assert(token != NULL && temp != NULL, \
		MASSERT "(toekn != NULL && temp != NULL), " \
		TOKENIZE_INTERNAL MTOKENIZE_FILE "line 34.");
	ft_lstadd_back(chunks, temp);
	return (end + 1);
}

void	tokenize(char *input, t_lst **chunks)
{
	char	*begin;
	char	*end;

	begin = input;
	while (*begin)
	{
		while (ft_isspace(*begin))
			++begin;
		end = begin;
		while (*end && !ft_strchr(" ><|", *begin))
		{
			if (ft_strchr("\'\"", *end))
				end = ft_strchr(end + 1, *end);
			if (ft_strchr("><|", *(end + 1)) || (*end != '\\' && *(end
						+ 1) == ' '))
				break ;
			++end;
		}
		if (!*end)
			--end;
		if (*begin && *begin == *(begin + 1) && ft_strchr("><", *begin))
			++end;
		if (*begin)
			begin = tokenize_internal(input, begin, end, chunks);
	}
}
