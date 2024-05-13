/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonhseo <wonhseo@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 04:58:05 by wonhseo           #+#    #+#             */
/*   Updated: 2024/05/14 06:44:06 by wonhseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_exit(char **args)
{
	bool	valid;
	char	*search;

	valid = true;
	search = *(args + 1);
	while (search != NULL && *search)
		if (!ft_isdigit(*search++))
			valid = false;
	if (!valid)
	{
		ft_putstr("exit\nexit: ", STDERR_FILENO);
		ft_putstr(*(args + 1), STDERR_FILENO);
		ft_putendl(": " NUMERIC, STDERR_FILENO);
		exit(RANGE);
	}
	else if (valid && *(args + 1) != NULL && *(args + 2) != NULL)
	{
		ft_putendl("exit\nexit: " SEVERAL, STDERR_FILENO);
		return (BUILTIN);
	}
	ft_putendl("exit", STDOUT_FILENO);
	if (*(args + 1) == NULL)
		exit(VALID);
	exit(ft_atoi(*(args + 1)));
}
