/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonhseo <wonhseo@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 04:57:25 by wonhseo           #+#    #+#             */
/*   Updated: 2024/05/14 06:42:47 by wonhseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
# ifndef OPEN_MAX
#  define OPEN_MAX 4096
# endif
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif

typedef enum e_stat
{
	ERROR = -1,
	END,
	SUCCESS,
}					t_stat;
typedef struct s_lst
{
	void			*content;
	struct s_lst	*next;
}					t_lst;
size_t				ft_abs(int n);
int					ft_atoi(const char *s);
bool				ft_calloc(void **ptr, size_t cnt, size_t n);
void				ft_free(void **ptr);
int					ft_gnl(int fd, char **line);
bool				ft_isalnum(int c);
int					ft_isalpha(int c);
bool				ft_isascii(int c);
bool				ft_isdigit(int c);
bool				ft_isprint(int c);
bool				ft_isspace(int c);
char				*ft_itoa(int n);
void				ft_lstadd_back(t_lst **lst, t_lst *new_node);
void				ft_lstadd_front(t_lst **lst, t_lst *new_node);
void				ft_lstclear(t_lst **lst, void (*del)(void **));
void				ft_lstdelone(t_lst *lst, void (*del)(void **));
void				ft_lstiter(t_lst *lst, void (*f)(void *));
t_lst				*ft_lstlast(t_lst *lst);
t_lst				*ft_lstmap(t_lst *lst, void *(*f)(void *),
						void (*del)(void **));
t_lst				*ft_lstnew(void *content);
void				ft_lstshow(t_lst *lst);
size_t				ft_lstsize(t_lst *lst);
void				*ft_memset(void *s, int c, size_t n);
size_t				ft_numlen(int v);
void				ft_putchar(char c, int fd);
void				ft_putendl(char *s, int fd);
void				ft_putnbr(int n, int fd);
void				ft_putstr(char *s, int fd);
char				**ft_split(const char *s, bool (*cmp)(int));
bool				ft_strappend(char **s, char *s2);
char				*ft_strchr(const char *s, int c);
char				*ft_strdup(const char *s);
char				*ft_strjoin(const char *s1, const char *s2);
size_t				ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t				ft_strlen(const char *s);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strrchr(const char *s, int c);
void				ft_strtrim(char **s);
char				*ft_substr(const char *s, unsigned int start, size_t len);
int					ft_tolower(int c);
int					ft_toupper(int c);
size_t				ft_wordlen(const char *s, bool (*cmp)(int));
#endif
