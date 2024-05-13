/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdr_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonhseo <wonhseo@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 04:58:39 by wonhseo           #+#    #+#             */
/*   Updated: 2024/05/14 05:57:45 by wonhseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_rdr_gt(t_as *syntax)
{
	int	fd;

	fd = open(syntax->left->token, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	mini_assert(fd >= 0, \
		MASSERT "(fd >= 0), " EXEC_RDR_GT MRDR_2_FILE "line 28.");
	mini_assert(dup2(fd, STDOUT_FILENO) != ERROR, \
		MASSERT "(dup2(fd, STDOUT_FILENO) != ERROR), " \
		EXEC_RDR_GT MRDR_2_FILE "line 30.");
	close(fd);
}

bool	exec_rdr_lt(t_as *syntax, t_rb *envmap)
{
	int	fd;

	fd = open(syntax->left->token, O_RDONLY, S_IRWXU);
	if (fd < 0)
	{
		rb_insert(envmap, ft_strdup("?"), ft_strdup(ft_itoa(GENERAL)));
		finish(syntax->left->token, false);
		return (false);
	}
	mini_assert(dup2(fd, STDIN_FILENO) != ERROR, \
		MASSERT "(dup2(fd, STDIN_FILENO) != ERROR), " \
		EXEC_RDR_LT MRDR_2_FILE "line 55.");
	close(fd);
	return (true);
}

void	exec_rdr_rshift(t_as *syntax)
{
	int	fd;

	fd = open(syntax->left->token, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
	mini_assert(fd >= 0, \
		MASSERT "(fd >= 0), " EXEC_RDR_RSHIFT MRDR_2_FILE "line 74.");
	mini_assert(dup2(fd, STDOUT_FILENO) != ERROR, \
		MASSERT "(dup2(fd, STDOUT_FILENO) != ERROR), " \
		EXEC_RDR_RSHIFT MRDR_2_FILE "line 76.");
	close(fd);
}

static inline void	handle(int fd, char *input, t_rb *envmap)
{
	input = expand(input, envmap, false);
	ft_putendl(input, fd);
	ft_free((void **)(&input));
}

void	exec_rdr_lshift(t_as *syntax, t_rb *envmap)
{
	int		fd;
	char	*input;

	echoctl_off();
	fd = open(HEREDOC, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	mini_assert(fd >= 0, \
		MASSERT "(fd >= 0), " EXEC_RDR_LSHIFT MRDR_2_FILE "line 117.");
	while (true)
	{
		input = readline("> ");
		if (input == NULL || !ft_strncmp(input, syntax->left->token,
				BUFFER_SIZE))
			break ;
		handle(fd, input, envmap);
	}
	ft_free((void **)(&input));
	close(fd);
	fd = open(HEREDOC, O_RDONLY, S_IRWXU);
	mini_assert(fd >= 0, \
		MASSERT "(fd >= 0), " EXEC_RDR_LSHIFT MRDR_2_FILE "line 129.");
	mini_assert(dup2(fd, STDIN_FILENO) != ERROR, \
		MASSERT "(dup2(fd, STDOUT_FILENO) != ERROR), " \
		EXEC_RDR_LSHIFT MRDR_2_FILE "line 131.");
	close(fd);
}
