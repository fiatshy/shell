/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_dollar_set.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghyki <sunghyki@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:53:16 by sunghyki          #+#    #+#             */
/*   Updated: 2024/05/16 17:53:17 by sunghyki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_test.h"

void	handle_dollar_compare(char split_env[4][100], \
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
	env_len = ft_strlen(split_env_input[1]);
	ft_memcpy(result_string + front_len, split_env_input[1], env_len);
	end_len = ft_strlen(split_env[2]);
	ft_memcpy(result_string + front_len + env_len, split_env[2], end_len);
	result_string[front_len + env_len + end_len] = 0;
	free(split_arg[i]);
	split_arg[i] = result_string;
}

void	handle_flag(char **split_arg, int i)
{
	free(split_arg[i]);
	split_arg[i] = malloc (2);
	split_arg[i][0] = ' ';
	split_arg[i][1] = 0;
}

void	handle_dollar_nested(char split_env[4][100], \
	char **split_arg, int i, t_cmd_struct *tcst)
{
	char	**split_env_input;
	t_list	*temp;
	t_list	*prev;
	int		flag;

	flag = true;
	prev = NULL;
	temp = *tcst->lst_env;
	while (temp)
	{
		split_env_input = ft_split(temp->content, '=');
		if (ft_strncmp(split_env[1], split_env_input[0], \
			ft_strlen(split_env_input[0])) == 0)
		{
			flag = false;
			handle_dollar_compare(split_env, split_arg, i, split_env_input);
			break ;
		}
		free_env_input(split_env_input);
		temp = temp->next;
	}
	if (flag)
		handle_flag(split_arg, i);
}

void	handle_dollar(char **split_arg, int i, t_cmd_struct	*tcst)
{
	int		result;
	int		dollar;
	int		space;
	char	split_env[4][100];
	int		j;

	result = is_double_is_outer(split_arg[i]);
	dollar = has_dollar(split_arg[i]);
	space = space_after_dollar(split_arg[i] + dollar);
	split_environ(split_arg[i], dollar, space, split_env);
	if (result && dollar)
		handle_dollar_nested(split_env, split_arg, i, tcst);
}
