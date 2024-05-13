/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonhseo <wonhseo@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 04:57:53 by wonhseo           #+#    #+#             */
/*   Updated: 2024/05/14 06:43:52 by wonhseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline int	rollback(char *oldpath, char *newpath, int ret)
{
	ft_free((void **)(&oldpath));
	ft_free((void **)(&newpath));
	return (ret);
}

static inline char	*tilt(char *arg, t_rb *envmap)
{
	if (*arg == '~')
		return (ft_strjoin(get_value(envmap, "HOME"), arg + 1));
	else
		return (ft_strdup(arg));
}

int	builtin_cd(char **args, t_rb *envmap)
{
	int		ret;
	char	*oldpath;
	char	*newpath;

	if (*(args + 1) == NULL)
		newpath = ft_strdup(get_value(envmap, "HOME"));
	else
		newpath = tilt(*(args + 1), envmap);
	oldpath = getcwd(NULL, 0);
	if (oldpath == NULL || newpath == NULL)
		return (rollback(oldpath, newpath, BUILTIN));
	ret = chdir(newpath);
	if (ret < 0)
	{
		ft_putstr("cd: ", STDERR_FILENO);
		ft_putstr(newpath, STDERR_FILENO);
		ft_putendl(": " ENTRIES, STDERR_FILENO);
		return (rollback(oldpath, newpath, BUILTIN));
	}
	ft_free((void **)(&newpath));
	rb_insert(envmap, ft_strdup("OLDPWD"), oldpath);
	rb_insert(envmap, ft_strdup("PWD"), getcwd(NULL, 0));
	return (VALID);
}
