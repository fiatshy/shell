/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonhseo <wonhseo@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 04:58:33 by wonhseo           #+#    #+#             */
/*   Updated: 2024/05/14 06:45:21 by wonhseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>

static inline pid_t	out_process(t_as *syntax, t_rb *envmap, int fd[2])
{
	pid_t	pid;

	set_signal(SIG_IGN, SIG_IGN);
	pid = fork();
	mini_assert(pid != ERROR, \
		MASSERT "(pid != ERROR), " OUT_PROCESS MPIPE_FILE "line 31.");
	if (!pid)
	{
		set_signal(SIG_DFL, SIG_DFL);
		close(fd[IN]);
		mini_assert(dup2(fd[OUT], STDOUT_FILENO) != ERROR, \
			MASSERT "(dup2(fd[OUT], STDOUT_FILENO) != ERROR)" \
			OUT_PROCESS MPIPE_FILE "line 37.");
		close(fd[OUT]);
		syntax->exec(syntax, envmap);
		exit(VALID);
	}
	return (pid);
}

static inline pid_t	in_process(t_as *syntax, t_rb *envmap, int fd[2])
{
	pid_t	pid;

	set_signal(SIG_IGN, SIG_IGN);
	pid = fork();
	mini_assert(pid != ERROR, \
		MASSERT "(pid != ERROR), " IN_PROCESS MPIPE_FILE "line 63.");
	if (!pid)
	{
		set_signal(SIG_DFL, SIG_DFL);
		close(fd[OUT]);
		mini_assert(dup2(fd[IN], STDIN_FILENO) != ERROR, \
			MASSERT "(dup2(fd[IN], STDIN_FILENO) != ERROR)" \
			IN_PROCESS MPIPE_FILE "line 69.");
		close(fd[IN]);
		syntax->exec(syntax, envmap);
		exit(VALID);
	}
	return (pid);
}

void	exec_pipe(t_as *syntax, t_rb *envmap)
{
	int		fd[2];
	pid_t	lchild;
	pid_t	rchild;

	mini_assert(pipe(fd) != ERROR, \
		MASSERT "(pipe(fd) != ERROR), " EXEC_PIPE MPIPE_FILE "line 96.");
	rchild = out_process(syntax->right, envmap, fd);
	waitpid(rchild, NULL, 0);
	close(fd[OUT]);
	lchild = in_process(syntax->left, envmap, fd);
	waitpid(lchild, NULL, 0);
	close(fd[IN]);
	set_signal(customized, SIG_IGN);
}
