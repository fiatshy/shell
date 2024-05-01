/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghyki <sunghyki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 20:19:23 by sunghyki          #+#    #+#             */
/*   Updated: 2024/03/04 20:19:38 by sunghyki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*init(t_index *t, int fd, char (*c)[ARR_SIZE])
{
	if (fd == 0)
		t->fd_idx = 0;
	else
		t->fd_idx = fd - 3;
	if (!check_param_errors(fd))
	{
		free(t);
		return (NULL);
	}
	t->i = has(c[t->fd_idx], 0);
	if (!(t->i))
		ft_bzero(c[t->fd_idx], ARR_SIZE);
	t->r = (int) read(fd, c[t->fd_idx] + t->i, BUFFER_SIZE);
	if (t->r == -1)
	{
		free(t);
		return (NULL);
	}
	t->i += t->r;
	t->idx = has(c[t->fd_idx], 1);
	return ((void *)(1));
}

void	*read_file(t_index *t, int fd, char (*c)[ARR_SIZE])
{
	while (!t->idx && t->r != 0)
	{
		t->r = (int) read(fd, c[t->fd_idx] + t->i, BUFFER_SIZE);
		if (t->r == -1)
		{
			free(t);
			return (0);
		}
		t->i += t->r;
		t->idx = has(c[t->fd_idx], 1);
	}
	if (t->idx == 0 && t->i == 0)
	{
		free(t);
		return (NULL);
	}
	return ((void *)1);
}

void	count_letters(t_index *t)
{
	t->leftover_length = t->i - t->idx;
	if (t->r != 0 && BUFFER_SIZE != 0)
		t->i = t->i - (BUFFER_SIZE - (mod(t->idx, BUFFER_SIZE)));
	if ((int)t->i < 0)
		t->i = 0;
	t->k = 0;
	if (t->r != 0 || t->idx != 0)
		t->k = t->idx;
	else if (t->r == 0 || t->idx == 0)
		t->k = t->i;
}

void	clear_and_prepare_next(t_index *t, char (*c)[ARR_SIZE])
{
	t->k = 0;
	t->j = t->idx;
	while (t->k < t->j)
		c[t->fd_idx][t->k++] = 0;
	t->j = 0;
	while (t->j < t->leftover_length)
	{
		c[t->fd_idx][t->j] = c[t->fd_idx][t->idx];
		c[t->fd_idx][t->idx] = 0;
		t->j++;
		t->idx++;
	}
	c[t->fd_idx][t->j] = -1;
}

void	copy_return_str(t_index *t, char *line_str, char (*c)[ARR_SIZE])
{
	t->j = 0;
	while (t->j < t->k)
	{
		line_str[t->j] = c[t->fd_idx][t->j];
		t->j++;
	}
	line_str[t->j] = 0;
}
