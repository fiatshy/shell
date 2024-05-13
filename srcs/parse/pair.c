/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonhseo <wonhseo@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 05:01:05 by wonhseo           #+#    #+#             */
/*   Updated: 2024/05/14 06:45:40 by wonhseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline void	pair_argc(int argc, t_rb *envmap)
{
	rb_insert(envmap, ft_strdup("#"), ft_itoa(argc - 1));
}

static inline void	pair_argv(int argc, char **argv, t_rb *envmap)
{
	int		i;
	char	*str;
	char	*temp;

	i = 0;
	temp = ft_strdup("");
	while (++i < argc)
	{
		str = ft_strjoin(temp, argv[i]);
		ft_free((void **)(&temp));
		temp = str;
		if (i == argc - 1)
			break ;
		str = ft_strjoin(temp, " ");
		ft_free((void **)(&temp));
		temp = str;
	}
	if (argc == 1)
		str = temp;
	mini_assert(str != NULL, \
		MASSERT "(str != NULL), " PAIR_ARGV MPAIR_FILE "line 41.");
	rb_insert(envmap, ft_strdup("*"), str);
}

void	pair(int argc, char **argv, char **envp, t_rb *envmap)
{
	int		level;
	char	*value;

	while (*envp != NULL)
	{
		value = ft_strchr(*envp, '=');
		*value++ = '\0';
		rb_insert(envmap, ft_strdup(*envp++), ft_strdup(value));
	}
	level = ft_atoi(get_value(envmap, "SHLVL")) + 1;
	if (ft_strrchr(argv[0], '/'))
	{
		argv[0] = ft_strrchr(argv[0], '/');
		++(argv[0]);
	}
	rb_insert(envmap, ft_strdup("PS1"), ft_strjoin(argv[0], "$ "));
	rb_insert(envmap, ft_strdup("SHLVL"), ft_itoa(level));
	rb_insert(envmap, ft_strdup("?"), ft_itoa(0));
	rb_insert(envmap, ft_strdup("_"), ft_strdup("minishell"));
	pair_argc(argc, envmap);
	pair_argv(argc, argv, envmap);
}
