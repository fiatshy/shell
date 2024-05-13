/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonhseo <wonhseo@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 04:58:20 by wonhseo           #+#    #+#             */
/*   Updated: 2024/05/14 06:45:00 by wonhseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>

static inline bool	is_builtin(t_as *syntax)
{
	int		i;
	char	*lower;
	bool	builtin;

	i = -1;
	lower = ft_strdup(syntax->token);
	builtin = false;
	mini_assert(lower != NULL, \
		MASSERT "(lower != NULL), " IS_BUILTIN MCOMMAND_1_FILE "line 34.");
	while (lower[++i])
		lower[i] = ft_tolower(lower[i]);
	if (!ft_strncmp("cd", lower, BUFFER_SIZE) || !ft_strncmp("echo", lower,
			BUFFER_SIZE) || !ft_strncmp("env", lower, BUFFER_SIZE)
		|| !ft_strncmp("exit", lower, BUFFER_SIZE) || !ft_strncmp("export",
			lower, BUFFER_SIZE) || !ft_strncmp("pwd", lower, BUFFER_SIZE)
		|| !ft_strncmp("unset", lower, BUFFER_SIZE))
		builtin = true;
	ft_free((void **)(&lower));
	return (builtin);
}

static inline int	exec_builtin(char *command, char **args, t_rb *envmap)
{
	int	i;

	i = -1;
	while (command[++i])
		command[i] = ft_tolower(command[i]);
	if (!ft_strncmp("cd", command, BUFFER_SIZE))
		return (builtin_cd(args, envmap));
	else if (!ft_strncmp("echo", command, BUFFER_SIZE))
		return (builtin_echo(args));
	else if (!ft_strncmp("env", command, BUFFER_SIZE))
		return (builtin_env(envmap));
	else if (!ft_strncmp("exit", command, BUFFER_SIZE))
		return (builtin_exit(args));
	else if (!ft_strncmp("export", command, BUFFER_SIZE))
		return (builtin_export(args, envmap));
	else if (!ft_strncmp("pwd", command, BUFFER_SIZE))
		return (builtin_pwd());
	else if (!ft_strncmp("unset", command, BUFFER_SIZE))
		return (builtin_unset(args, envmap));
	else
		return (BUILTIN);
}

static inline pid_t	binary_internal(char *command, char **args, t_rb *envmap)
{
	pid_t	pid;
	char	*path;
	char	**envp;

	set_signal(SIG_IGN, SIG_IGN);
	pid = fork();
	envp = NULL;
	mini_assert(pid != ERROR, \
		MASSERT "(pid != ERROR), " \
		BINARY_INTERNAL MCOMMAND_1_FILE "line 106.");
	if (!pid)
	{
		set_signal(SIG_DFL, SIG_DFL);
		configure(&envp, envmap->root);
		if (*command == '.')
			path = resolve(command, envmap);
		else if (*command == '/')
			path = command;
		else
			path = find(command, envmap);
		execve(path, args, envp);
		finish(path, true);
	}
	return (pid);
}

static inline int	exec_binary(char *command, char **args, t_rb *envmap)
{
	pid_t	pid;
	int		ret;
	int		status;

	pid = binary_internal(command, args, envmap);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		ret = WEXITSTATUS(status);
	else
	{
		ret = WTERMSIG(status);
		if (ret == SIGQUIT)
			ft_putendl("Quit: 3", STDERR_FILENO);
		else
			ft_putendl("", STDERR_FILENO);
		ret = SIGOFFSET + ret;
	}
	return (ret);
}

void	exec_cmd(t_as *syntax, t_rb *envmap)
{
	int		i;
	int		ret;
	char	**args;

	i = -1;
	arrange(syntax->token);
	args = capture(syntax);
	while (args[++i] != NULL)
		arrange(args[i]);
	if (is_builtin(syntax))
		ret = exec_builtin(syntax->token, args, envmap);
	else
		ret = exec_binary(syntax->token, args, envmap);
	rb_insert(envmap, ft_strdup("?"), ft_itoa(ret));
	set_signal(customized, SIG_IGN);
	delete(&args);
}
