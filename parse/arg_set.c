/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghyki <sunghyki@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:53:21 by sunghyki          #+#    #+#             */
/*   Updated: 2024/05/16 17:53:22 by sunghyki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_test.h"

void	set_arguments_nested(t_cmd *tcmd, int i, \
	t_cmd_struct *tcst, char **split_arg)
{
	tcmd->arg = malloc (sizeof(char *) * (get_length_of_args(split_arg) + 1));
	while (split_arg[i])
	{
		if (has_double_quote(split_arg[i]))
			handle_dollar(split_arg, i, tcst);
		else if (have_quote(split_arg[i]) == 0 && \
			have_dollar_nonzero(split_arg[i]))
			handle_noquote_dollar(&split_arg[i], tcst);
		copy_string_char(&tcmd->arg[i], \
			split_arg[i], ft_strlen(split_arg[i]));
		free(split_arg[i]);
		i++;
	}
	if (i != 0)
		tcmd->arg[i] = 0;
	free(split_arg);
}

int	set_arguments(t_cmd *tcmd, t_cmd_struct *tcst)
{
	int		i;
	char	**split_arg;

	i = 0;
	if (has_asterisk(tcmd->cmd) == 1)
	{
		split_arg = split_asterisk(tcmd->cmd);
		if (split_arg[1] == 0)
			return (-1);
	}
	else
		split_arg = ft_split_quote(tcmd->cmd, ' ');
	set_arguments_nested(tcmd, i, tcst, split_arg);
	return (0);
}
