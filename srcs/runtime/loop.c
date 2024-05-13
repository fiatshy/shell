/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonhseo <wonhseo@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 05:01:45 by wonhseo           #+#    #+#             */
/*   Updated: 2024/05/14 06:46:10 by wonhseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline void	execute(t_lst *chunks, t_as *syntax, t_rb *envmap)
{
	syntax = as_init(chunks);
	echoctl_on();
	as_exec(syntax, envmap);
	echoctl_off();
	as_free(syntax);
}

void	loop(char *input, t_lst *chunks, t_as *syntax, t_rb *envmap)
{
	while (true)
	{
		ft_free((void **)(&input));
		input = readline(get_value(envmap, "PS1"));
		if (input == NULL)
		{
			ft_putendl("exit", STDOUT_FILENO);
			exit(VALID);
		}
		if (!ft_strlen(input) || empty(input))
			continue ;
		add_history(input);
		if (!quotes(input) && set_rl(input, QUOTES, STDERR_FILENO, false))
			continue ;
		input = expand(input, envmap, false);
		mini_assert(input != NULL, \
			MASSERT "(input != NULL), " LOOP MLOOP_FILE "line 60.");
		tokenize(input, &chunks);
		mini_assert(chunks != NULL, \
			MASSERT "(chunks != NULL), " LOOP MLOOP_FILE "line 64.");
		execute(chunks, syntax, envmap);
		ft_lstclear(&chunks, ft_free);
	}
}

void	finish(char *entry, bool shutdown)
{
	if (errno)
		ft_putstr(entry, STDERR_FILENO);
	if (errno == ENOENT)
	{
		ft_putendl(": " ENTRIES, STDERR_FILENO);
		if (shutdown)
			exit(GENERAL);
	}
	if (errno == EFAULT)
	{
		ft_putendl(": " COMMANDS, STDERR_FILENO);
		if (shutdown)
			exit(NOTFOUND);
	}
	if (errno == EACCES)
	{
		ft_putendl(": " PERMISSIONS, STDERR_FILENO);
		if (shutdown)
			exit(NOTEXECUTABLE);
	}
	if (shutdown)
		exit(VALID);
}
