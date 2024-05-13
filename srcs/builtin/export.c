/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonhseo <wonhseo@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 04:58:09 by wonhseo           #+#    #+#             */
/*   Updated: 2024/05/14 06:44:14 by wonhseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline void	print(t_node *node)
{
	if (node == NULL)
		return ;
	print(node->left);
	print(node->right);
	if (!ft_strncmp((char *)(node->key), "#", BUFFER_SIZE)
		|| !ft_strncmp((char *)(node->key), "*", BUFFER_SIZE)
		|| !ft_strncmp((char *)(node->key), "?", BUFFER_SIZE))
		return ;
	ft_putstr("declare -x ", STDOUT_FILENO);
	ft_putstr((char *)(node->key), STDOUT_FILENO);
	if (!*(char *)(node->value))
	{
		ft_putendl("", STDOUT_FILENO);
		return ;
	}
	ft_putstr("=\"", STDOUT_FILENO);
	ft_putstr((char *)(node->value), STDOUT_FILENO);
	ft_putendl("\"", STDOUT_FILENO);
}

static inline void	logic_internal(char *search, char *arg, t_rb *envmap)
{
	*search++ = '\0';
	if (!ft_strncmp(arg, "PS1", BUFFER_SIZE))
		rb_insert(envmap, ft_strdup(arg), ft_strjoin(search, " "));
	else
		rb_insert(envmap, ft_strdup(arg), ft_strdup(search));
}

static inline void	logic(char *arg, t_rb *envmap)
{
	char	*search;
	char	*value;

	search = ft_strchr(arg, '=');
	if (search == NULL)
	{
		value = get_value(envmap, arg);
		if (!value)
			rb_insert(envmap, ft_strdup(arg), ft_strdup(""));
	}
	else if (*(search - 1) == '+')
	{
		*(search - 1) = '\0';
		*search++ = '\0';
		value = get_value(envmap, arg);
		if (value == NULL)
			value = "";
		rb_insert(envmap, ft_strdup(arg), ft_strjoin(value, search));
	}
	else
		logic_internal(search, arg, envmap);
}

static inline bool	valid(char *search)
{
	int	i;

	i = -1;
	while (search[++i])
	{
		if (search[i] == '=' || (search[i] == '+' && search[i + 1] == '='))
			return (true);
		if (!(search[i] == '_' || ft_isalpha(search[i])
				|| ft_isdigit(search[i])))
			return (false);
	}
	return (true);
}

int	builtin_export(char **args, t_rb *envmap)
{
	t_exit	ret;

	ret = VALID;
	if (*(args + 1) == NULL)
		print(envmap->root);
	else
	{
		while (*(++args) != NULL)
		{
			if ((**args != '_' && !ft_isalpha(**args)) || !valid(*args))
			{
				ret = BUILTIN;
				ft_putstr("export: `", STDERR_FILENO);
				ft_putstr(*args, STDERR_FILENO);
				ft_putendl("': " IDENTIFIER, STDERR_FILENO);
			}
			else
				logic(*args, envmap);
		}
	}
	return (ret);
}
