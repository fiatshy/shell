/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_nested.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghyki <sunghyki@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 14:36:05 by sunghyki          #+#    #+#             */
/*   Updated: 2024/05/17 14:36:07 by sunghyki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(t_cmd_struct *tcst, int index)
{
	tcst->builtin = 1;
	if (tcst->tcmd[index]->arg[1] == NULL)
	{
		chdir("/home/sunghyki");
		return ;
	}
	if (has_multi_dots(tcst->tcmd[index]->arg[1]) == -1)
	{
		printf("No such directory\n");
		return ;
	}
	if (has_relative_path(tcst->tcmd[index]->arg[1]))
		chdir(get_relative_path(tcst, index));
	else
	{
		tcst->status = 127;
		if (chdir(ft_strtrim(tcst->tcmd[index]->arg[1], "\"")) == -1)
			printf("No such directory\n");
	}
}

int	ft_env(t_cmd_struct *tcst)
{
	show_env_list(tcst->lst_env);
	return (0);
}

void	free_split_env(char **split_env)
{
	int	i;

	i = 0;
	while (split_env[i])
	{
		free(split_env[i]);
		i++;
	}
	free(split_env);
}

void	ft_export(t_cmd_struct *tcst, int index)
{
	t_list	*temp;
	char	**split_env;
	int		flag;

	flag = true;
	temp = *tcst->lst_env;
	while (temp)
	{
		split_env = ft_split(tcst->tcmd[index]->arg[1], '=');
		if (ft_strncmp(temp->content, split_env[0], \
			ft_strlen(split_env[0])) == 0)
		{
			free(temp->content);
			temp->content = malloc (ft_strlen(tcst->tcmd[index]->arg[1]) + 1);
			ft_memcpy(temp->content, tcst->tcmd[index]->arg[1], \
				ft_strlen(tcst->tcmd[index]->arg[1]) + 1);
			flag = false;
			free_split_env(split_env);
			break ;
		}
		free_split_env(split_env);
		temp = temp->next;
	}
	if (flag)
		ft_lstadd_back(tcst->lst_env, ft_lstnew(tcst->tcmd[index]->arg[1]));
}

void	ft_unset(t_cmd_struct *tcst, int index)
{
	t_list	*temp;
	t_list	*prev;

	prev = NULL;
	temp = *tcst->lst_env;
	while (temp)
	{
		if (ft_strncmp(temp->content, tcst->tcmd[index]->arg[1], \
			ft_strlen(tcst->tcmd[index]->arg[1])) == 0)
		{
			prev->next = temp->next;
			free(temp->content);
			temp = temp->next;
			break ;
		}
		prev = temp;
		temp = temp->next;
	}
}
