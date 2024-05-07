/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghyki <sunghyki@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 09:22:14 by sunghyki          #+#    #+#             */
/*   Updated: 2024/05/07 09:22:21 by sunghyki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "parse_test.h"

void	handle_interrupt(int fill)
{
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_interrupt_blocked(int fill)
{
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
}

void	fork_and_exectue_nested(t_cmd_struct *tcst, int index)
{
	if (tcst->tcmd[index]->pipe_index != -1)
	{
		if (index < tcst->no_of_pipes)
			close(tcst->tpipe[index].fd[1]);
	}
}

char	*get_env(void)
{
	int	fd;
	int	i;
	char	*temp;
	char	**split;

	fd = open("environment", O_RDONLY);
	temp = get_next_line(fd);
	while (temp)
	{
		if (ft_strncmp(temp, "PATH", 4) == 0)
		{
			split = ft_split(temp, '=');
			free(temp);
			return (split[1]);
		}
		free(temp);
		temp = get_next_line(fd);
	}
	free(temp);
	close(fd);
	return (NULL);
}

void	get_execute_path_nested(int *response, char *s, char **cmd_path)
{
	int			i;
	char		*path;
	char		**split_path;
	struct stat	buf;

	path = get_env();
	if (path != NULL)
		split_path = ft_split(path, ':');
	else
		split_path = NULL;
	i = 0;
	if (path == NULL && split_path == NULL)
		printf("Wrong Command\n");
	while (split_path[i])
	{
		*cmd_path = ft_strjoin(split_path[i], "/");
		*cmd_path = ft_strjoin(*cmd_path, s);
		if (stat(*cmd_path, &buf) == 0)
		{
			*response = 1;
			break ;
		}
		i++;
	}
}

char	*get_exectue_path(char *s)
{	char	*split;
	struct stat	buf;
	char		*cmd_path;
	int			response;

	response = 0;
	if (stat(s, &buf) == 0)
	{
		cmd_path = s;
		response = 1;
	}
	else
		get_execute_path_nested(&response, s, &cmd_path);
	if (response == 0)
		return (0);
	return (cmd_path);
}

void	set_tunnels(t_cmd_struct *tcst, int index)
{
	if (tcst->tcmd[index]->pipe_index != -1)
	{
		if (tcst->tcmd[index]->pipe_index == 0)
			set_pipe_head(tcst, tcst->tcmd[index]->pipe_index);
		else if (tcst->tcmd[index]->pipe_index == tcst->no_of_pipes)
			set_pipe_tail(tcst, tcst->tcmd[index]->pipe_index);
		else
			set_pipe_body(tcst, tcst->tcmd[index]->pipe_index);
	}
}

void	trim(t_cmd_struct *tcst, int index, int i)
{
	char	*temp;

	temp = ft_strtrim(tcst->tcmd[index]->arg[i], "\"");
	temp = ft_strtrim(temp, "\'");
	printf("%s ", temp);
	free(temp);
}

void	ft_echo(t_cmd_struct *tcst, int index)
{
	char	*temp;
	int		i;

	if (ft_strncmp("-n", tcst->tcmd[index]->arg[1], 2) == 0)
	{
		i = 2;
		while (tcst->tcmd[index]->arg[i])
		{
			trim(tcst, index, i);
			i++;
		}
	}
	else
	{
		i = 1;
		while (tcst->tcmd[index]->arg[i])
		{
			trim(tcst, index, i);
			i++;
		}
		printf("\n");
	}
}

void	ft_exit(void)
{
	/* implement exit */
}

void	ft_status(t_cmd_struct *tcst)
{
	printf("%d\n", tcst->status);
}

void	ft_pwd(t_cmd_struct *tcst)
{
	char	buf[255];

	getcwd(buf, 255);
	printf("%s\n", buf);
}

int	find_slash_reverse(char *s, int target)
{
	int	len;
	int	count;

	count = 0;
	len = ft_strlen(s);
	while (len > 0)
	{
		if (*(s + len) == '/')
			count++;
		if (count == target)
			return (len);
		len--;
	}
	return (0);
}

char	*extract_command(t_cmd_struct *tcst, int index)
{
	int		start;
	int		length;
	char	*temp_command;

	start = find_slash_reverse(tcst->tcmd[index]->arg[1], 1);
	length = ft_strlen(tcst->tcmd[index]->arg[1]);
	temp_command = malloc (length - start);
	ft_memcpy(temp_command, tcst->tcmd[index]->arg[1] + \
		start + 1, length - start - 1);
	temp_command[length - start - 1] = 0;
	return (temp_command);
}

void	delete_redundant_path(char temp[255], int start)
{
	int	i;

	i = start;
	while (i < 255)
	{
		temp[i] = 0;
		i++;
	}
	if (start == 0)
		temp[0] = '/';
}

void	copy_path(char temp[255], char *src)
{
	int	i;

	while (temp[i])
		i++;
	temp[i] = '/';
	i++;
	while (*src)
	{
		temp[i] = *src;
		i++;
		src++;
	}
}

char	*relative_path_exec_nested(t_cmd_struct *tcst, int index, char cwd[255])
{
	int		ret_length;
	char	*ret_string;

	ret_length = ft_strlen(cwd);
	ret_string = malloc (ret_length + 1);
	ft_memcpy(ret_string, cwd, ret_length);
	ret_string[ret_length] = 0;
	return (ret_string);
}

char	*get_relative_path(t_cmd_struct *tcst, int index)
{
	int		i;
	char	**split_slash;
	char	cwd[255];
	int		slash_length;
	char	*ret_string;

	split_slash = ft_split(tcst->tcmd[index]->arg[1], '/');
	i = 0;
	getcwd(cwd, 255);
	while (split_slash[i])
	{
		if (ft_strncmp("..", split_slash[i], 2) == 0)
		{
			slash_length = find_slash_reverse(cwd, 1);
			delete_redundant_path(cwd, slash_length);
		}
		else
			copy_path(cwd, split_slash[i]);
		i++;
	}
	ret_string = relative_path_exec_nested(tcst, index, cwd);
	return (ret_string);
}

char	*get_relative_path_exec(t_cmd_struct *tcst, int index)
{
	int		i;
	char	**split_slash;
	char	cwd[255];
	int		slash_length;
	char	*ret_string;

	split_slash = ft_split(tcst->tcmd[index]->arg[0], '/');
	i = 0;
	getcwd(cwd, 255);
	while (split_slash[i])
	{
		if (ft_strncmp("..", split_slash[i], 2) == 0)
		{
			slash_length = find_slash_reverse(cwd, 1);
			delete_redundant_path(cwd, slash_length);
		}
		else
			copy_path(cwd, split_slash[i]);
		i++;
	}
	ret_string = relative_path_exec_nested(tcst, index, cwd);
	return (ret_string);
}

int	has_relative_path(char *s)
{
	while (1)
	{
		if (ft_strncmp(s, "..", 2) == 0)
			return (1);
		s++;
		if (*s == 0)
			break ;
	}
	return (0);
}

void	ft_cd(t_cmd_struct *tcst, int index)
{
	char	buf[255];

	getcwd(buf, 255);
	if (has_relative_path(tcst->tcmd[index]->arg[1]))
	{
		chdir(get_relative_path(tcst, index));
	}
	else
		chdir(tcst->tcmd[index]->arg[1]);
}

int	ft_env(void)
{
	int		fd;
	int		i;
	char	*temp;

	fd = open("environment", O_RDONLY);
	i = 0;
	temp = get_next_line(fd);
	while (temp)
	{
		printf("%s", temp);
		free(temp);
		temp = get_next_line(fd);
	}
	free(temp);
	close(fd);
	return (0);
}

void	ft_export(t_cmd_struct *tcst, int index)
{
	int	fd;

	fd = open("environment", O_RDWR | O_APPEND, 0777);
	write(fd, tcst->tcmd[index]->arg[1], ft_strlen(tcst->tcmd[index]->arg[1]));
	write(fd, "\n", 1);
	close(fd);
}

void	get_file_length(int *i)
{
	int		fd;
	char	*temp;

	fd = open("environment", O_RDWR, 0777);
	*i = 0;
	temp = get_next_line(fd);
	while (temp)
	{
		(*i)++;
		temp = get_next_line(fd);
		free(temp);
	}
	free(temp);
	close(fd);
}

void	write_env(char **arr, t_cmd_struct *tcst, int index)
{
	int		fd;
	int		i;
	char	**temp_split;

	remove("environment");
	fd = open("environment", O_CREAT | O_WRONLY, 0777);
	i = 0;
	while (arr[i])
	{
		temp_split = ft_split(arr[i], '=');
		if (ft_strncmp(temp_split[0], tcst->tcmd[index]->arg[1], \
			ft_strlen(temp_split[0])) != 0)
			write(fd, arr[i], ft_strlen(arr[i]));
		free(temp_split[0]);
		free(temp_split[1]);
		free(temp_split);
		i++;
	}
	close(fd);
}

void	ft_unset(t_cmd_struct *tcst, int index)
{
	int		fd;
	int		i;
	char	**arr;

	get_file_length(&i);
	arr = malloc (sizeof(char *) * (i + 1));
	i = 0;
	fd = open("environment", O_RDWR, 0777);
	arr[i] = get_next_line(fd);
	while (arr[i])
	{
		i++;
		arr[i] = get_next_line(fd);
	}
	close(fd);
	write_env(arr, tcst, index);
}

int	is_builtin(t_cmd_struct *tcst, int index)
{
	if (ft_strncmp("echo", tcst->tcmd[index]->arg[0], 4) == 0)
		return (1);
	else if (ft_strncmp("exit", tcst->tcmd[index]->arg[0], 4) == 0)
		return (2);
	else if (ft_strncmp("$?", tcst->tcmd[index]->arg[0], 2) == 0)
		return (1);
	else if (ft_strncmp("pwd", tcst->tcmd[index]->arg[0], 3) == 0)
		return (1);
	else if (ft_strncmp("cd", tcst->tcmd[index]->arg[0], 3) == 0)
		return (3);
	else if (ft_strncmp("env", tcst->tcmd[index]->arg[0], 3) == 0)
		return (1);
	else if (ft_strncmp("export", tcst->tcmd[index]->arg[0], 6) == 0)
		return (1);
	else if (ft_strncmp("unset", tcst->tcmd[index]->arg[0], 5) == 0)
		return (1);
	return (0);
}

int	exec_builtin(t_cmd_struct *tcst, int index)
{
	if (ft_strncmp("echo", tcst->tcmd[index]->arg[0], 4) == 0)
		ft_echo(tcst, index);
	else if (ft_strncmp("exit", tcst->tcmd[index]->arg[0], 4) == 0)
		ft_exit();
	else if (ft_strncmp("$?", tcst->tcmd[index]->arg[0], 2) == 0)
		ft_status(tcst);
	else if (ft_strncmp("pwd", tcst->tcmd[index]->arg[0], 3) == 0)
		ft_pwd(tcst);
	else if (ft_strncmp("cd", tcst->tcmd[index]->arg[0], 3) == 0)
		ft_cd(tcst, index);
	else if (ft_strncmp("env", tcst->tcmd[index]->arg[0], 3) == 0)
		ft_env();
	else if (ft_strncmp("export", tcst->tcmd[index]->arg[0], 6) == 0)
		ft_export(tcst, index);
	else if (ft_strncmp("unset", tcst->tcmd[index]->arg[0], 5) == 0)
		ft_unset(tcst, index);
	return (1);
}

int	handle_res(int *res, t_cmd_struct *tcst, int index)
{
	*res = is_builtin(tcst, index);
	if (*res == 2)
		exit(0);
	if (*res == 3)
	{
		ft_cd(tcst, index);
		return (1);
	}
	return (0);
}

void	handle_parent(int res, t_cmd_struct *tcst, int index)
{
	waitpid(0, &tcst->status, 0);
	fork_and_exectue_nested(tcst, index);
}

void	fork_nested(int res, t_cmd_struct *tcst, int index)
{
	char	**env;
	char	*command;

	env = NULL;
	if (res == 1)
	{
		exec_builtin(tcst, index);
		exit(0);
	}
	else if (res == 0)
	{
		if (has_relative_path(tcst->tcmd[index]->arg[0]))
			command = get_exectue_path(get_relative_path_exec(tcst, index));
		else
			command = get_exectue_path(tcst->tcmd[index]->arg[0]);
		if (command == 0)
			printf("Wrong command\n");
		else
		{
			execve(command, tcst->tcmd[index]->arg, env);
			exit(0);
		}
	}
	exit(0);
}

int	fork_and_execute(t_cmd_struct *tcst, int index)
{
	int		pid;
	char	*command;
	int		res;

	if (handle_res(&res, tcst, index) == 1)
		return (0);
	signal(SIGINT, handle_interrupt_blocked);
	signal(SIGQUIT, handle_interrupt_blocked);
	pid = fork();
	if (pid == 0)
	{
		set_tunnels(tcst, index);
		fork_nested(res, tcst, index);
	}
	else if (res != 3)
		handle_parent(res, tcst, index);
}

void	free_after_exectue(t_cmd_struct *tcst, int i, int *proceed)
{
	int	j;

	j = 0;
	if (i < tcst->n)
	{
		while (tcst->tcmd[i]->arg[j])
		{
			free(tcst->tcmd[i]->arg[j]);
			j++;
		}
		free(tcst->tcmd[i]->arg);
		*proceed = true;
	}
}

int	check_grouping_or(t_cmd_struct *tcst, int *i, int *proceed)
{
	if (tcst->status == 0)
	{
		*proceed = false;
		if (tcst->open)
		{
			*i += get_closed_index(tcst, *i);
			tcst->open = 0;
			return (-1);
		}
	}
	else if (tcst->status != 0)
		*proceed = true;
}

int	check_grouping_and(t_cmd_struct *tcst, int *i, int *proceed)
{
	if (tcst->status == 0)
		*proceed = true;
	else if (tcst->status != 0)
	{
		*proceed = false;
		if (tcst->open)
		{
			*i += get_closed_index(tcst, *i);
			tcst->open = 0;
			return (-1);
		}
	}
}

int	check_grouping(t_cmd_struct *tcst, int *i, int *proceed)
{
	int	res;

	if (*i != 0)
	{
		if (ft_strncmp(tcst->tcmd[*i - 1]->next_delimiter, "||", 2) == 0)
		{
			res = check_grouping_or(tcst, i, proceed);
			if (res == -1)
				return (-1);
		}
		else if (ft_strncmp(tcst->tcmd[*i - 1]->next_delimiter, "&&", 2) == 0)
		{
			res = check_grouping_and(tcst, i, proceed);
			if (res == -1)
				return (-1);
		}
	}
	return (0);
}

void	set_redirect_args(t_cmd_struct *tcst, int *index, int k)
{
	if (k == 0 && ft_strncmp(tcst->trst->split_again[k], "<", 1) \
			&& ft_strncmp(tcst->trst->split_again[k], ">", 1))
	{
		tcst->trst->args[*index] = malloc \
			(sizeof(ft_strlen(tcst->trst->split_again[k]) + 1));
		ft_memcpy(tcst->trst->args[*index], \
			tcst->trst->split_again[k], \
				ft_strlen(tcst->trst->split_again[k]) + 1);
		*index += 1;
	}
	else if (k != 0 && ft_strncmp(tcst->trst->split_again[k - 1], "<", 1) \
			&& ft_strncmp(tcst->trst->split_again[k - 1], ">", 1))
	{
		if (ft_strncmp(tcst->trst->split_again[k], "<", 1) \
			&& ft_strncmp(tcst->trst->split_again[k], ">", 1))
		{
			tcst->trst->args[*index] = malloc \
			(sizeof(ft_strlen(tcst->trst->split_again[k]) + 1));
			ft_memcpy(tcst->trst->args[*index], \
			tcst->trst->split_again[k], \
			ft_strlen(tcst->trst->split_again[k]) + 1);
			*index += 1;
		}
	}
}

void	handle_redirect_delim_nested(t_cmd_struct *tcst, int k)
{
	close(tcst->tfd[tcst->tfd_index[0]].tmp);
	tcst->tfd[tcst->tfd_index[0]].tmp = open("tmp", O_RDWR);
	tcst->tfd_index[0] += 1;
}

void	handle_redirect_delim(t_cmd_struct *tcst, int k)
{
	int		r;
	char	temp[100];

	if (ft_strncmp(tcst->trst->split_again[k], "<<", 2) == 0)
	{
		tcst->tfd[tcst->tfd_index[0]].tmp = \
			open("tmp", O_CREAT | O_RDWR | O_TRUNC, 0777);
		while (1)
		{
			ft_memset(temp, 0, 100);
			r = read(0, temp, 100);
			if (ft_strncmp(temp, tcst->trst->split_again[k + 1], \
				ft_strlen(temp) - 1) == 0)
				break ;
			else
				write(tcst->tfd[tcst->tfd_index[0]].tmp, temp, r);
		}
		handle_redirect_delim_nested(tcst, k);
	}
	else if (ft_strncmp(tcst->trst->split_again[k], "<", 1) == 0)
	{
		tcst->tfd[tcst->tfd_index[1]].read = \
			open(tcst->trst->split_again[k + 1], O_RDONLY, 0777);
		tcst->tfd_index[1] += 1;
	}
}

void	handle_redirect_output(t_cmd_struct *tcst, int k)
{
	if (ft_strncmp(tcst->trst->split_again[k], ">>", 2) == 0)
	{
		tcst->tfd[tcst->tfd_index[2]].append = \
			open(tcst->trst->split_again[k + 1], \
				O_WRONLY | O_CREAT | O_APPEND, 0777);
		tcst->tfd_index[2] += 1;
	}
	else if (ft_strncmp(tcst->trst->split_again[k], ">", 1) == 0)
	{
		tcst->tfd[tcst->tfd_index[3]].write = \
			open(tcst->trst->split_again[k + 1], \
				O_WRONLY | O_CREAT, 0777);
		tcst->tfd_index[3] += 1;
	}
}

void	handle_again(t_cmd_struct *tcst, int k, int *index)
{
	set_redirect_args(tcst, index, k);
	handle_redirect_delim(tcst, k);
	handle_redirect_output(tcst, k);
}

void	free_again(t_cmd_struct *tcst, int k)
{
	int	i;

	i = 0;
	while (i < k)
	{
		free(tcst->trst->split_again[i]);
		i++;
	}
	free(tcst->trst->split_again);
}

int	free_redirect_all(t_cmd_struct *tcst)
{
	int	l;

	l = 0;
	while (l < 2)
	{
		free(tcst->trst->args[l]);
		l++;
	}
	free(tcst->trst->args);
	free(tcst->trst);
}

void	init_dup2(t_cmd_struct *tcst)
{
	int	i;

	i = 0;
	while (i < 10)
	{
		if (tcst->tfd[i].write > 0)
			dup2(tcst->tfd[i].write, 1);
		if (tcst->tfd[i].append > 0)
			dup2(tcst->tfd[i].append, 1);
		if (tcst->tfd[i].tmp > 0)
			dup2(tcst->tfd[i].tmp, 0);
		if (tcst->tfd[i].read > 0)
			dup2(tcst->tfd[i].read, 0);
		i++;
	}
}

void	close_fds(t_cmd_struct *tcst)
{
	int	i;

	i = 0;
	while (i < 10)
	{
		if (tcst->tfd[i].write > 0)
			close(tcst->tfd[i].write);
		if (tcst->tfd[i].append > 0)
			close(tcst->tfd[i].append);
		if (tcst->tfd[i].tmp > 0)
			close(tcst->tfd[i].tmp);
		if (tcst->tfd[i].read > 0)
			close(tcst->tfd[i].read);
		i++;
	}
}

char	*make_bin(t_cmd_struct *tcst)
{
	char	*command;

	command = get_exectue_path(tcst->trst->args[0]);
	return (command);
}

void	set_tunnel_redirect(t_cmd_struct *tcst, int index)
{
	if (tcst->tcmd[index]->pipe_index != -1)
	{
		if (tcst->tcmd[index]->pipe_index == 0)
			set_pipe_head(tcst, tcst->tcmd[index]->pipe_index);
		else if (tcst->tcmd[index]->pipe_index == tcst->no_of_pipes)
			set_pipe_tail(tcst, tcst->tcmd[index]->pipe_index);
		else
			set_pipe_body(tcst, tcst->tcmd[index]->pipe_index);
	}
}


void	redirect_parents(t_cmd_struct *tcst, int index)
{
	waitpid(0, &tcst->status, 0);
	close_fds(tcst);
	if (index < tcst->no_of_pipes)
		close(tcst->tpipe[index].fd[1]);
}

void	execute_redirection(t_cmd_struct *tcst, int first, int index)
{
	int		pid;
	char	**envs;
	char	*bin;
	char	*command;

	pid = fork();
	envs = NULL;
	if (pid == 0)
	{
		init_dup2(tcst);
		set_tunnel_redirect(tcst, index);
		command = make_bin(tcst);
		if (command == 0)
			printf("Wrong command.");
		else
			execve(make_bin(tcst), tcst->trst->args, envs);
		return ;
	}
	else
		redirect_parents(tcst, index);
	close_fds(tcst);
	free_redirect_all(tcst);
}

void	free_redirection(t_cmd_struct *tcst, int j)
{
	int	l;

	l = 0;
	while (l < j)
	{
		free(tcst->trst->split_redirection[l]);
		l++;
	}
	free(tcst->trst->split_redirection);
}

int	get_args_length(char **s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (i == 0)
		{
			if (ft_strncmp(s[i], ">", 1) && ft_strncmp(s[i], "<", 1))
				count++;
		}
		else
		{
			if (ft_strncmp(s[i - 1], ">", 1) && ft_strncmp(s[i - 1], "<", 1))
				if (ft_strncmp(s[i], ">", 1) && ft_strncmp(s[i], "<", 1))
					count++;
		}
		i++;
	}
	return (count);
}

void	handle_redirection_nested(t_cmd_struct *tcst, int j)
{
	int	k;
	int	index;
	int	length;

	while (tcst->trst->split_redirection[j])
	{
		tcst->trst->split_again = \
			ft_split(tcst->trst->split_redirection[j], ' ');
		k = 0;
		index = 0;
		length = get_args_length(tcst->trst->split_again);
		tcst->trst->args = malloc (sizeof(char *) * (length + 1));
		tcst->trst->args[length] = 0;
		while (tcst->trst->split_again[k])
		{
			handle_again(tcst, k, &index);
			k++;
		}
		free_again(tcst, k);
		j++;
	}
	free_redirection(tcst, j);
}

void	handle_redirection(t_cmd_struct *tcst, int i)
{
	int		j;
	int		k;
	int		first;
	int		index;

	tcst->trst = malloc (sizeof(t_red_struct));
	tcst->trst->split_redirection = ft_split(tcst->tcmd[i]->cmd, '=');
	j = 0;
	tcst->trst->args = malloc (sizeof(char *) * 2);
	handle_redirection_nested(tcst, j);
	execute_redirection(tcst, first, i);
}

void	prepare_execute(t_cmd_struct *tcst)
{
	int		i;
	int		no_of_redirection;
	int		proceed;
	int		cont;

	i = 0;
	cont = 0;
	proceed = 1;
	while (i < tcst->n)
	{
		no_of_redirection = get_no_of_redirection(tcst->tcmd[i]);
		if (no_of_redirection == 0)
		{
			set_arguments(tcst->tcmd[i]);
			cont = check_grouping(tcst, &i, &proceed);
			if (cont == -1)
				continue ;
			if (proceed)
				fork_and_execute(tcst, i);
			free_after_exectue(tcst, i, &proceed);
		}
		else
			handle_redirection(tcst, i);
		i++;
	}
}

int	free_all(t_cmd_struct *tcst, t_pipe *tp)
{
	int	i;
	int	temp;

	//free(tp);
	i = 0;
	temp = tcst->status;
	while (i < tcst->n)
	{
		free(tcst->tcmd[i]->cmd);
		free(tcst->tcmd[i]);
		i++;
	}
	//free(tcst->tfd);
	free(tcst->tcmd);
	free(tcst);
	return (temp);
}

int	has_only_spaces(char *s)
{
	while (*s)
	{
		if (*s != ' ' && *s != '\t')
			return (0);
		s++;
	}
	return (1);
}

int	is_empty_command(char s)
{
	if (s == 0)
		return (1);
	return (0);
}

void handle_quit()
{
    //printf("hello");
}

int	check_if_ctrl_d(char *s)
{
	while (*s)
	{
		if (*s == '\n')
			return (0);
		s++;
	}
	return (1);
}

int	main(void)
{
	t_cmd			**tcmd;
	t_cmd_struct	*tcst;
	t_pipe			*tp;
	int				status = 0;

	char			*s;

	signal(SIGINT, handle_interrupt);
	signal(SIGQUIT, SIG_IGN); //SIGIGN reverse slash
	while (1)
	{
		s = readline("shell $ ");
		if (s == 0)
			exit(0);
		if (is_empty_command(s[0]) || has_only_spaces(s))
			continue ;
		add_history(s);
		init_tcst(&tcst, s, status);
		copy_string_char(&(tcst->s), s, ft_strlen(s));
		init_tcmd(tcst);
		tcst->no_of_pipes = get_no_of_pipes(tcst);
		init_pipe(tcst, &tp);
		prepare_execute(tcst);
		signal(SIGINT, handle_interrupt);
		signal(SIGQUIT, SIG_IGN);
		status = free_all(tcst, tp);
	}

	/* not solved*/
	// ls -al | dude
	// (ls -al || grep) hello
	// (ls -al && grep shell) || ls jvice versa
	
	/* solved */
	// ls -al && (ls -al | grep shell)
	// (ls -al || grep ) && ls
	// (ls -al && grep) || echo this
	// < a grep a > b && ls

	//char			*s = "<< a grep a > b | ls -a";
	//char	*s = "echo \"\'this $USER that\'\"";
	//char	*s = "< a grep a | grep a | wc -l > b";
	//char	*s = "< a grep a | wc -l > b";
	//char	*s = "test ../../../../../usr/bin/ls";
	//char	*s = "cd ../../../../../../usr/bin/";
	// char	*s = "ls | grep a*";
	// char	*s = "echo there $USER is";

	//char	*s = "echo 'there | you go'";
	//init_tcst(&tcst, s, status);
	//copy_string_char(&(tcst->s), s, ft_strlen(s));
	//init_tcmd(tcst);
	//tcst->no_of_pipes = get_no_of_pipes(tcst);
	//init_pipe(tcst, &tp);
	//prepare_execute(tcst);
	//free_all(tcst, tp);
}
