/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonhseo <wonhseo@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 04:58:15 by wonhseo           #+#    #+#             */
/*   Updated: 2024/05/14 06:44:24 by wonhseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_unset(char **args, t_rb *envmap)
{
	t_exit	ret;

	ret = VALID;
	if (*(args + 1) == NULL)
		return (ret);
	while (*(++args) != NULL)
	{
		if (!ft_isalpha(**args))
		{
			ret = BUILTIN;
			ft_putstr("unset: `", STDERR_FILENO);
			ft_putstr(*args, STDERR_FILENO);
			ft_putendl("': " IDENTIFIER, STDERR_FILENO);
		}
		else
			rb_delete(envmap, *args);
	}
	return (ret);
}
