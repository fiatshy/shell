/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghyki <sunghyki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 20:06:04 by sunghyki          #+#    #+#             */
/*   Updated: 2024/03/11 12:21:55 by sunghyki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	mod(size_t a, size_t b)
{
	return (a % b);
}

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		*(char *)(s + i) = 0;
		i++;
	}
}

int	has(char *s, int flag)
{
	int	j;

	j = 0;
	if (flag == 0)
	{
		while (*(s + j) != 0)
		{
			if (*(s + j) == -1)
			{
				*(s + j) = 0;
				return (j);
			}
			j++;
		}
	}
	else if (flag == 1)
	{
		while (*(s + j) != 0)
		{
			if (*(s + j) == '\n')
				return (j + 1);
			j++;
		}
	}
	return (0);
}

void	*check_param_errors(int fd)
{
	if ((fd < 3 && fd != 0) || fd == -1)
		return (NULL);
	if (BUFFER_SIZE <= 0)
		return (NULL);
	return ((void *)1);
}

char	*get_next_line(int fd)
{
	static char	c[ARR_SIZE][ARR_SIZE];
	char		*line_str;
	t_index		*t;

	t = (t_index *) malloc (sizeof(t_index));
	if (init(t, fd, c) == NULL)
		return (0);
	if (read_file(t, fd, c) == NULL)
		return (0);
	count_letters(t);
	line_str = (char *) malloc (sizeof(char) * (t->k + 1));
	if (!line_str)
	{
		free(t);
		return (0);
	}
	copy_return_str(t, line_str, c);
	clear_and_prepare_next(t, c);
	free(t);
	return (line_str);
}
