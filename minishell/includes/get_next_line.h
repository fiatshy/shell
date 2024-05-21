/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghyki <sunghyki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 20:10:26 by sunghyki          #+#    #+#             */
/*   Updated: 2024/03/04 20:10:31 by sunghyki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif
# ifndef ARR_SIZE
#  define ARR_SIZE 2000
# endif
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct s_index
{
	size_t	i;
	size_t	j;
	size_t	k;
	size_t	idx;
	size_t	leftover_length;
	int		r;
	int		fd_idx;
	char	*line_str;
}				t_index;

//static char 	c[ARR_SIZE][ARR_SIZE];

char	*get_next_line(int fd);
void	*init(t_index *t, int fd, char (*c)[ARR_SIZE]);
void	*read_file(t_index *t, int fd, char (*c)[ARR_SIZE]);
void	count_letters(t_index *t);
void	clear_and_prepare_next(t_index *t, char (*c)[ARR_SIZE]);
void	copy_return_str(t_index *t, char *line_str, char (*c)[ARR_SIZE]);
void	*check_param_errors(int fd);
int		has(char *s, int flag);
void	ft_bzero(void *s, size_t n);
size_t	mod(size_t a, size_t b);

#endif
