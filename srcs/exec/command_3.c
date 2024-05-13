/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonhseo <wonhseo@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 04:58:26 by wonhseo           #+#    #+#             */
/*   Updated: 2024/05/14 05:19:55 by wonhseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	compare(int c)
{
	return (c == ':');
}

static inline bool	check(char *command, char *chunk, DIR *current)
{
	bool			exist;
	char			*abs;
	struct stat		data;
	struct dirent	*reader;

	exist = false;
	reader = readdir(current);
	while (reader != NULL)
	{
		if (!ft_strncmp(reader->d_name, command, BUFFER_SIZE))
		{
			abs = ft_strjoin(ft_strjoin(chunk, "/"), reader->d_name);
			if (lstat(abs, &data) != ERROR)
				if (data.st_mode & S_IXUSR)
					exist = true;
		}
		reader = readdir(current);
	}
	if (exist)
		closedir(current);
	return (exist);
}

static inline char	*search(char *command, char *candidates)
{
	char	**chunks;
	DIR		*current;

	chunks = ft_split(candidates, compare);
	while (*chunks != NULL)
	{
		current = opendir(*chunks);
		if (current == NULL)
		{
			++chunks;
			continue ;
		}
		if (check(command, *chunks, current))
			break ;
		closedir(current);
		++chunks;
	}
	return (*chunks);
}

char	*find(char *command, t_rb *envmap)
{
	char	*abs;
	char	*candidates;

	candidates = ft_strdup(get_value(envmap, "PATH"));
	if (candidates == NULL)
	{
		errno = ENOENT;
		finish(command, true);
	}
	abs = search(command, candidates);
	if (abs != NULL)
		return (ft_strjoin(ft_strjoin(abs, "/"), command));
	else
	{
		errno = EFAULT;
		finish(command, true);
	}
	return (NULL);
}

char	*resolve(char *command, t_rb *envmap)
{
	int		ret;
	char	*sep;
	char	*abs;

	sep = command;
	while (ft_strchr(sep + 1, '/') != NULL)
		sep = ft_strchr(sep + 1, '/');
	*sep = '\0';
	ret = chdir(command);
	*sep = '/';
	if (ret < 0)
	{
		errno = ENOENT;
		finish(command, true);
	}
	abs = getcwd(NULL, 0);
	if (search(sep + 1, abs) == NULL)
	{
		errno = ENOENT;
		finish(command, true);
	}
	chdir(get_value(envmap, "PWD"));
	return (ft_strjoin(abs, sep));
}
