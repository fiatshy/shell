/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   relative_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghyki <sunghyki@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 14:36:44 by sunghyki          #+#    #+#             */
/*   Updated: 2024/05/17 14:36:46 by sunghyki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_test.h"

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

char	*relative_path_exec_nested(char cwd[255])
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
	ret_string = relative_path_exec_nested(cwd);
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
	ret_string = relative_path_exec_nested(cwd);
	return (ret_string);
}
