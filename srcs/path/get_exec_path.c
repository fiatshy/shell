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

void	get_execute_path_nested(int *response, \
	char *s, char **cmd_path, t_cmd_struct *tcst)
{
	int			i;
	char		*path;
	char		**split_path;
	struct stat	buf;

	path = get_envv(tcst);
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
		return (0);
	return (cmd_path);
}
