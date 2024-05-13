/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonhseo <wonhseo@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 04:58:23 by wonhseo           #+#    #+#             */
/*   Updated: 2024/05/14 06:44:55 by wonhseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

static inline char	**stretch(char **args, size_t size)
{
	int		i;
	char	**res;

	i = -1;
	ft_calloc((void **)(&res), size + 1, sizeof(char *));
	mini_assert(res != NULL, \
		MASSERT "(res != NULL), " STRETCH MCOMMAND_2_FILE "line 32.");
	while (args[++i] != NULL)
	{
		res[i] = ft_strdup(args[i]);
		mini_assert(res[i] != NULL, \
			MASSERT "(res[i] != NULL), " \
			STRETCH MCOMMAND_2_FILE "line 37.");
	}
	delete(&args);
	return (res);
}

static inline void	accumulate(char ***args, char *chunk)
{
	size_t	size;

	size = 0;
	if (*args == NULL)
	{
		ft_calloc((void **)(args), 2, sizeof(char *));
		mini_assert(*args != NULL, \
			MASSERT "(*args != NULL), " \
			ACCUMULATE MCOMMAND_2_FILE "line 60.");
		**args = ft_strdup(chunk);
		mini_assert(**args != NULL, \
			MASSERT "(**args != NULL), " \
			ACCUMULATE MCOMMAND_2_FILE "line 64.");
	}
	else
	{
		while ((*args)[size] != NULL)
			++size;
		*args = stretch(*args, size + 1);
		(*args)[size] = ft_strdup(chunk);
		mini_assert((*args)[size] != NULL, \
			MASSERT "((*args)[size] != NULL), " \
			ACCUMULATE MCOMMAND_2_FILE "line 74.");
	}
}

char	**capture(t_as *syntax)
{
	char	**args;
	t_as	*search;

	args = NULL;
	accumulate(&args, syntax->token);
	search = syntax->right;
	while (search != NULL)
	{
		accumulate(&args, search->token);
		search = search->right;
	}
	return (args);
}

void	configure(char ***envp, t_node *node)
{
	char	*entry;

	if (node == NULL)
		return ;
	configure(envp, node->left);
	configure(envp, node->right);
	if (!ft_strncmp((char *)(node->key), "#", BUFFER_SIZE)
		|| !ft_strncmp((char *)(node->key), "*", BUFFER_SIZE)
		|| !ft_strncmp((char *)(node->key), "?", BUFFER_SIZE))
		return ;
	if (!*((char *)(node->value)))
		return ;
	entry = ft_strjoin((char *)(node->key), "=");
	ft_strappend(&entry, (char *)(node->value));
	accumulate(envp, entry);
}

void	delete(char ***args)
{
	int	i;

	if (*args == NULL)
		return ;
	i = -1;
	while ((*args)[++i] != NULL)
		ft_free((void **)(&((*args)[i])));
	ft_free((void **)(&((*args)[i])));
	ft_free((void **)(&(*args)));
}
