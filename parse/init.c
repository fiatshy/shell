/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghyki <sunghyki@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 09:21:08 by sunghyki          #+#    #+#             */
/*   Updated: 2024/05/07 09:21:11 by sunghyki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_test.h"

void	init_fds(t_cmd_struct *tcst)
{
	int	i;

	i = 0;
	while (i < 10)
	{
		tcst->tfd[i].append = -1;
		tcst->tfd[i].read = -1;
		tcst->tfd[i].tmp = -1;
		tcst->tfd[i].write = -1;
		i++;
	}
}

int	has_double_quote(char *split_arg)
{
	while (*split_arg)
	{
		if (*split_arg == '"')
			return (1);
		split_arg++;
	}
	return (0);
}

int	is_double_is_outer(char *split_arg)
{
	while (*split_arg)
	{
		if (*split_arg == '\'')
			return (0);
		else if (*split_arg == '\"')
			return (1);
		split_arg++;
	}
	return (0);
}

int	has_dollar(char *split_arg)
{
	int	i;

	i = 0;
	while (*(split_arg + i))
	{
		if (*(split_arg + i) == '$')
			return (i);
		i++;
	}
	return (0);
}

int	space_after_dollar(char *string)
{
	int	i;

	i = 0;
	while (*(string + i))
	{
		if (*(string + i) == ' ')
			return (i);
		i++;
	}
	return (i);
}

char	**split_environ(char *string, int s, int e)
{
	char	**temp;
	int		len;

	if (e <= 0)
		e = 5;
	temp = malloc (sizeof(char *) * 4);
	temp[0] = malloc (s + 1);
	ft_memcpy(temp[0], string, s);
	temp[0][s] = 0;
	temp[1] = malloc (e + 1);
	ft_memcpy(temp[1], string + s + 1, e - 1);
	temp[1][e - 1] = 0;
	len = ft_strlen(string);
	temp[2] = malloc (len - (s + e) + 1);
	ft_memcpy(temp[2], string + s + e, len - (s + e));
	temp[2][len - (s + e)] = 0;
	temp[3] = 0;
	return (temp);
}

void	handle_dollar_compare(char **split_env, \
	char **split_arg, int i, char **split_env_input)
{
	char	*result_string;
	char	*remove_quote;
	int		front_len;
	int		env_len;
	int		end_len;

	result_string = malloc (ft_strlen(split_env[0]) + \
		ft_strlen(split_env[2]) + ft_strlen(split_env_input[1]));
	front_len = ft_strlen(split_env[0]);
	ft_memcpy(result_string, split_env[0], front_len);
	env_len = ft_strlen(split_env_input[1]) - 1;
	ft_memcpy(result_string + front_len, split_env_input[1], env_len);
	end_len = ft_strlen(split_env[2]);
	ft_memcpy(result_string + front_len + env_len, split_env[2], end_len);
	result_string[front_len + env_len + end_len] = 0;
	remove_quote = ft_strtrim(result_string, "\"");
	free(result_string);
	free(split_arg[i]);
	split_arg[i] = remove_quote;
}

void	free_env_input(char **split_env_input)
{
	int	j;

	j = 0;
	while (split_env_input[j])
	{
		free(split_env_input[j]);
		j++;
	}
	free(split_env_input);
}

void	handle_dollar_nested(char **split_env, char **split_arg, int i, int j)
{
	int		fd;
	char	*input;
	char	**split_env_input;
	char	*result_string;
	char	*remove_quote;

	fd = open("environment", O_RDONLY, 0777);
	input = get_next_line(fd);
	while (input != NULL)
	{
		split_env_input = ft_split(input, '=');
		if (ft_strncmp(split_env[1], split_env_input[0], \
			ft_strlen(split_env_input[0])) == 0)
			handle_dollar_compare(split_env, split_arg, i, split_env_input);
		free_env_input(split_env_input);
		free(input);
		input = get_next_line(fd);
	}
	free(input);
	close(fd);
}

void	handle_dollar(char **split_arg, int i)
{
	int		result;
	int		dollar;
	int		space;
	char	**split_env;
	int		j;

	result = is_double_is_outer(split_arg[i]);
	dollar = has_dollar(split_arg[i]);
	space = space_after_dollar(split_arg[i] + dollar);
	split_env = split_environ(split_arg[i], dollar, space);
	if (result && dollar)
		handle_dollar_nested(split_env, split_arg, i, j);
	j = 0;
	while (split_env[j])
	{
		free(split_env[j]);
		j++;
	}
	free(split_env);
}

int	has_asterisk(char *s)
{
	while (*s)
	{
		if (*s == ' ')
		{
			while (*s == ' ')
			{
				s++;
			}
			break ;
		}
		s++;
	}
	while (*s)
	{
		if (*s == '*')
			return (1);
		s++;
	}
	return (0);
}

int	process_wildcard(char *f, char *t)
{
	while (*t)
	{
		if (*t == '*')
		{
			t++;
			while (*f)
			{
				if (*f == *t)
					break ;
				f++;
			}
		}
		else
		{
			if (*f == *t)
			{
				f++;
				t++;
			}
			else if (*f != *t)
				return (0);
		}
	}
	return (1);
}

int	how_much_files(char	*target)
{
	DIR				*dp;
	struct dirent	*entry;
	char			buf[255];
	int				count;

	count = 0;
	ft_memset(buf, 0, 255);
	getcwd(buf, 255);
	dp = opendir(buf);
	entry = readdir(dp);
	while (entry)
	{
		if (process_wildcard(entry->d_name, target))
			count++;
		entry = readdir(dp);
	}
	closedir(dp);
	return (count);
}

void	opendir_args(DIR **dp, struct dirent **entry)
{
	char	buf[255];

	ft_memset(buf, 0, 255);
	getcwd(buf, 255);
	*dp = opendir(buf);
	*entry = readdir(*dp);
}

char	**split_args(char *s, int length)
{
	DIR				*dp;
	struct dirent	*entry;
	char			buf[255];
	char			**ret;
	int				i;

	ret = malloc (sizeof(char *) * (length + 1));
	opendir_args(&dp, &entry);
	i = 1;
	while (entry)
	{
		if (process_wildcard(entry->d_name, s))
		{
			ret[i] = malloc (ft_strlen(entry->d_name));
			ft_memcpy(ret[i], entry->d_name, ft_strlen(entry->d_name));
			ret[i][ft_strlen(entry->d_name)] = 0;
			i++;
		}
		entry = readdir(dp);
	}
	ret[i] = 0;
	closedir(dp);
	return (ret);
}

char	**split_asterisk(char *s)
{
	char	**ret;
	char	**temp;
	int		length;

	temp = ft_split(s, ' ');
	length = how_much_files(temp[1]);
	ret = split_args(temp[1], length + 1);
	ret[0] = malloc (sizeof(ft_strlen(temp[0]) + 1));
	ft_memcpy(ret[0], temp[0], ft_strlen(temp[0]));
	ret[0][ft_strlen(temp[0])] = 0;
	free(temp[0]);
	free(temp[1]);
	free(temp);
	return (ret);
}

int	have_quote(char *s)
{
	while (*s)
	{
		if (*s == '\'' || *s == '"')
			return (1);
		s++;
	}
	return (0);
}

int	have_dollar_nonzero(char *s)
{
	while (*s)
	{
		if (*s == '$')
			return (1);
		s++;
	}
	return (0);
}

void	handle_noquote_dollar(char *s)
{
	int		fd;
	char	*input;
	char	**split_env;

	fd = open("environment", O_RDONLY, 0644);
	input = get_next_line(fd);
	while (input)
	{
		split_env = ft_split(input, '=');
		if (ft_strncmp(split_env[0], s + 1, ft_strlen(s + 1)) == 0)
		{
			free(s);
			s = malloc (ft_strlen(split_env[1]) + 1);
			ft_memcpy(s, split_env[1], ft_strlen(split_env[1]));
			s[ft_strlen(split_env[1]) - 1] = 0;
		}
		free(split_env[0]);
		free(split_env[1]);
		free(split_env);
		free(input);
		input = get_next_line(fd);
	}
	free(input);
	close(fd);
}

void	set_arguments(t_cmd *tcmd)
{
	int		i;
	char	**split_arg;

	i = 0;
	if (has_asterisk(tcmd->cmd) == 1)
		split_arg = split_asterisk(tcmd->cmd);
	else
		split_arg = ft_split_quote(tcmd->cmd, ' ');
	tcmd->arg = malloc (sizeof(char *) * (get_length_of_args(split_arg) + 1));
	while (split_arg[i])
	{
		if (has_double_quote(split_arg[i]))
			handle_dollar(split_arg, i);
		else if (have_quote(split_arg[i]) == 0 && \
			have_dollar_nonzero(split_arg[i]))
		{
			handle_noquote_dollar(split_arg[i]);
		}
		copy_string_char(&tcmd->arg[i], split_arg[i], ft_strlen(split_arg[i]));
		free(split_arg[i]);
		i++;
	}
	if (i != 0)
		tcmd->arg[i] = 0;
	free(split_arg);
}

void	init_tcst(t_cmd_struct **tcst, char *s, int status)
{
	int		i;
	t_fds	*tfd;

	(*tcst) = malloc (sizeof(t_cmd_struct));
	(*tcst)->n = get_no_of_command(s);
	if ((*tcst)->n == 0)
		(*tcst)->n = 1;
	(*tcst)->tcmd = malloc (sizeof(t_cmd));
	i = 0;
	while (i < (*tcst)->n)
	{
		(*tcst)->tcmd[i] = malloc (sizeof(t_cmd));
		i++;
	}
	(*tcst)->status = status;
	(*tcst)->tfd_index[0] = 0;
	(*tcst)->tfd_index[1] = 0;
	(*tcst)->tfd_index[2] = 0;
	(*tcst)->tfd_index[3] = 0;
	init_fds(*tcst);
}

void	nested_pipe_index(t_cmd_struct *tcst, int i)
{
	if (ft_strncmp(tcst->tcmd[i - 1]->next_delimiter, "||", 2) == 0 && \
			tcst->tcmd[i - 1]->pipe_index != -1)
		tcst->tcmd[i]->pipe_index = -1;
	else if (ft_strncmp(tcst->tcmd[i]->next_delimiter, "|", 1) == 0 || \
			tcst->tcmd[i - 1]->pipe_index != -1)
	{
		if (i != 0)
			tcst->tcmd[i]->pipe_index = tcst->tcmd[i - 1]->pipe_index + 1;
		else if (i == 0)
			tcst->tcmd[i]->pipe_index = 0;
	}
	else if (ft_strncmp(tcst->tcmd[i - 1]->next_delimiter, "&&", 2) == 0 && \
			tcst->tcmd[i - 1]->pipe_index != -1)
	{
		tcst->tcmd[i]->pipe_index = -1;
	}
}

void	set_pipe_index(t_cmd_struct *tcst, int i)
{
	tcst->tcmd[i]->pipe_index = -1;
	if (i != 0)
		nested_pipe_index(tcst, i);
	else if (i == 0)
	{
		if (ft_strncmp(tcst->tcmd[i]->next_delimiter, "|", 2) == 0)
			tcst->tcmd[i]->pipe_index = 0;
	}
}

void	free_init_tcmd(char **split, char *temp, char *trim_str)
{
	free(trim_str);
	free(split[0]);
	free(split[1]);
	free(split);
}

void	init_tcmd_set_openclose(t_cmd_struct *tcst, char **split, int i)
{
	if (has_open_parenthesis(split[0]))
	{
		tcst->tcmd[i]->open = true;
		tcst->open = 1;
	}
	if (has_close_parenthesis(split[0]))
		tcst->tcmd[i]->close = true;
}

void	init_tcmd(t_cmd_struct *tcst)
{
	int		i;
	char	**split;
	char	*temp;
	char	*trim_str;

	i = 0;
	copy_string_char(&temp, tcst->s, ft_strlen(tcst->s));
	free(tcst->s);
	while (i < tcst->n)
	{
		tcst->tcmd[i]->next_delimiter = get_first_delimiter(temp);
		set_pipe_index(tcst, i);
		split = ft_split_first(temp, ' ');
		init_tcmd_set_openclose(tcst, split, i);
		trim_str = ft_strtrim(split[0], " ()");
		copy_string(&tcst->tcmd[i], trim_str, ft_strlen(trim_str));
		if (temp != NULL)
			free(temp);
		if (split[1] != NULL)
			copy_string_char(&temp, split[1], ft_strlen(split[1]));
		free_init_tcmd(split, temp, trim_str);
		i++;
	}
}

void	init_pipe(t_cmd_struct *tcst, t_pipe **tp)
{
	int	i;

	i = 0;
	while (i < tcst->no_of_pipes)
	{
		pipe(tcst->tpipe[i].fd);
		i++;
	}
}
