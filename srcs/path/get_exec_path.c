/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_exec_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghyki <sunghyki@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 14:36:26 by sunghyki          #+#    #+#             */
/*   Updated: 2024/05/17 14:36:27 by sunghyki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_path(char **path)
{
	free(path[0]);
	free(path[1]);
	free(path);
}

void	path_nested(char **cmd_path, char *s, char **split_path, int *response)
{
	int			i;
	char		*temp_path;
	struct stat	buf;

	i = 0;
	while (split_path[i])
	{
		temp_path = ft_strjoin(split_path[i], "/");
		free(split_path[i]);
		*cmd_path = ft_strjoin(temp_path, s);
		free(temp_path);
		if (stat(*cmd_path, &buf) == 0)
		{
			*response = 1;
			break ;
		}
		free(*cmd_path);
		i++;
	}
}

void	get_execute_path_nested(int *response, \
	char *s, char **cmd_path, t_cmd_struct *tcst)
{
	char		**path;
	char		**split_path;

	path = get_envv(tcst);
	if (path != NULL)
		split_path = ft_split(path[1], ':');
	else
		split_path = NULL;
	if (path == NULL && split_path == NULL)
	{
		return ;
	}
	free_path(path);
	path_nested(cmd_path, s, split_path, response);
	free(split_path);
}

char	*get_exectue_path(char *s, t_cmd_struct *tcst)
{	
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
		get_execute_path_nested(&response, s, &cmd_path, tcst);
	if (response == 0)
	{
		tcst->status = 127;
		return (0);
	}
	return (cmd_path);
}
