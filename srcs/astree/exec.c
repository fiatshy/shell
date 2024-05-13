/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonhseo <wonhseo@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 04:57:39 by wonhseo           #+#    #+#             */
/*   Updated: 2024/05/14 06:43:30 by wonhseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "astree.h"

static inline void	rollback(int fd0, int fd1)
{
	dup2(fd0, STDIN_FILENO);
	dup2(fd1, STDOUT_FILENO);
	close(fd0);
	close(fd1);
}

void	as_exec(t_as *syntax, t_rb *envmap)
{
	int	fd[2];

	fd[0] = dup(STDIN_FILENO);
	fd[1] = dup(STDOUT_FILENO);
	if (!as_check(syntax))
		ft_putendl(SYNTAX, STDERR_FILENO);
	else
		syntax->exec(syntax, envmap);
	rollback(fd[0], fd[1]);
}
