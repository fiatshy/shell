/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gnl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonhseo <wonhseo@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 04:59:01 by wonhseo           #+#    #+#             */
/*   Updated: 2024/05/14 05:17:59 by wonhseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static inline bool	check_newline(char *mem, int *ret)
{
	int	i;

	i = -1;
	while (mem[++i])
	{
		if (mem[i] == '\n')
		{
			*ret = i;
			return (true);
		}
	}
	*ret = -1;
	return (false);
}

static inline int	split_line(char **mem, char **line, ssize_t idx)
{
	char	*tmp;

	(*mem)[idx] = '\0';
	*line = ft_strdup(*mem);
	if (!*line)
	{
		ft_free((void **)(mem));
		return (ERROR);
	}
	if (!ft_strlen(*mem + idx + 1))
	{
		ft_free((void **)(mem));
		return (SUCCESS);
	}
	tmp = *mem;
	*mem = ft_strdup(*mem + idx + 1);
	ft_free((void **)(&tmp));
	if (!*mem)
		return (ERROR);
	return (SUCCESS);
}

static inline int	exception_line(char **mem, char **line, int ret, char **buf)
{
	int	idx;

	idx = -1;
	ft_free((void **)(buf));
	if (ret < 0)
	{
		ft_free((void **)(mem));
		return (ERROR);
	}
	if (*mem)
	{
		if (check_newline(*mem, &idx))
			return (split_line(mem, line, idx));
		*line = *mem;
		*mem = NULL;
		return (END);
	}
	if (!ft_calloc((void **)(line), 1, sizeof(char)))
	{
		ft_free((void **)(mem));
		return (ERROR);
	}
	return (END);
}

int	ft_gnl(int fd, char **line)
{
	char		*buf;
	int			ret;
	static char	*mem[OPEN_MAX + 3];

	if (fd < 0 || !line || BUFFER_SIZE < 1 || OPEN_MAX <= fd
		|| !ft_calloc((void **)(&buf), BUFFER_SIZE + 1, sizeof(char)))
		return (ERROR);
	while (true)
	{
		ret = read(fd, buf, BUFFER_SIZE);
		if (ret <= 0)
			break ;
		buf[ret] = '\0';
		if (!ft_strappend(&(mem[fd]), buf))
		{
			ft_free((void **)(&buf));
			return (ERROR);
		}
		if (check_newline(mem[fd], &ret))
		{
			ft_free((void **)(&buf));
			return (split_line(&(mem[fd]), line, ret));
		}
	}
	return (exception_line(&(mem[fd]), line, ret, &buf));
}
