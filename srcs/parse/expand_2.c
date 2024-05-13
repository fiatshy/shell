/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonhseo <wonhseo@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 05:01:03 by wonhseo           #+#    #+#             */
/*   Updated: 2024/05/14 05:58:22 by wonhseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline void	expand_space(char *value, t_lst **brace)
{
	t_lst	*append;
	char	*search;

	*brace = NULL;
	search = value;
	while (true)
	{
		search = ft_strchr(value, ' ');
		if (search == NULL)
			break ;
		*search++ = '\0';
		append = ft_lstnew(ft_strdup(value));
		mini_assert(append != NULL && append->content != NULL, \
			MASSERT "(append != NULL && append->content != NULL), " \
			EXPAND_SPACE MEXPAND_1_FILE "line 39.");
		value = search;
		ft_lstadd_back(brace, append);
	}
	if (!*value)
		return ;
	append = ft_lstnew(ft_strdup(value));
	mini_assert(append != NULL && append->content != NULL, \
		MASSERT "(append != NULL && append->content != NULL), " \
		EXPAND_SPACE MEXPAND_1_FILE "line 48.");
	ft_lstadd_back(brace, append);
}

static inline char	*expand_brace(t_lst *brace)
{
	bool	ret;
	char	*middle;
	t_lst	*origin;

	middle = NULL;
	origin = brace;
	ret = ft_strappend(&middle, (char *)(brace->content));
	mini_assert(ret, MASSERT "(ret), " EXPAND_BRACE MEXPAND_1_FILE "line 73.");
	while (brace->next != NULL)
	{
		brace = brace->next;
		ret = ft_strappend(&middle, "\\ ");
		mini_assert(ret, \
			MASSERT "(ret), " EXPAND_BRACE MEXPAND_1_FILE "line 78.");
		ret = ft_strappend(&middle, (char *)(brace->content));
		mini_assert(ret, \
			MASSERT "(ret), " EXPAND_BRACE MEXPAND_1_FILE "line 81.");
	}
	ft_lstclear(&origin, ft_free);
	return (middle);
}

static inline char	*expand_middle(char *input, char *it, char *last,
		t_rb *envmap)
{
	char	*key;
	char	*value;
	t_lst	*brace;

	if (last - it == 1)
		return (ft_strdup("$"));
	key = ft_substr(input, it - input + 1, last - it - 1);
	value = get_value(envmap, key);
	if (value == NULL)
		value = "";
	ft_free((void **)(&key));
	value = ft_strdup(value);
	if (value == NULL || !*value)
		return (value);
	expand_space(value, &brace);
	mini_assert(brace != NULL, \
		MASSERT "(brace != NULL), " EXPAND_MIDDLE MEXPAND_1_FILE "line 118.");
	ft_free((void **)(&value));
	return (expand_brace(brace));
}

static inline char	*expand_last(char *it)
{
	if (*it && ft_strchr("$?$#*", *it))
		++it;
	else
		while (*it && !ft_strchr(" ><\'\"|?$", *it))
			++it;
	return (it);
}

char	*expand_internal(char *input, char *it, t_rb *envmap, bool d_quote)
{
	char	*first;
	char	*last;
	char	*middle;
	char	*former;
	char	*latter;

	first = ft_substr(input, 0, it - input);
	last = expand_last(it + 1);
	middle = expand_middle(input, it, last, envmap);
	last = ft_strdup(last);
	former = ft_strjoin(first, middle);
	latter = expand(last, envmap, d_quote);
	ft_free((void **)(&middle));
	ft_free((void **)(&first));
	ft_free((void **)(&input));
	input = ft_strjoin(former, latter);
	ft_free((void **)(&latter));
	ft_free((void **)(&former));
	return (input);
}
