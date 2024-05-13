/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonhseo <wonhseo@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 04:57:58 by wonhseo           #+#    #+#             */
/*   Updated: 2024/05/14 06:43:56 by wonhseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_echo(char **args)
{
	int	option;

	option = 0;
	if (*(args + 1) == NULL)
	{
		ft_putchar('\n', STDOUT_FILENO);
		return (VALID);
	}
	if (!ft_strncmp("-n", *(++args), BUFFER_SIZE))
		++option;
	args += option;
	while (*args != NULL)
	{
		ft_putstr(*args, STDOUT_FILENO);
		if (*(args + 1) != NULL)
			ft_putchar(' ', STDOUT_FILENO);
		++args;
	}
	if (!option)
		ft_putchar('\n', STDOUT_FILENO);
	return (VALID);
}
