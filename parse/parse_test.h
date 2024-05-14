#include <sys/wait.h>
#include <signal.h>
#include <stdio.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/types.h>
#include "libft/libft.h"
#include "get_next_line.h"

typedef struct  s_cmd
{
	char    *cmd;
	char    **arg;
	char    **env;
	char	*next_delimiter;
	bool	execute;
	int		open;
	int		close;
	int		no_of_redirection;
	int		pipe_index;
}               t_cmd;

typedef struct  s_pipe
{
	int fd[2];
}               t_pipe;

typedef struct	s_fds
{
	int	write;
	int	read;
	int	append;
	int	tmp;
}				t_fds;

typedef struct	s_red_struct
{
	char	**split_redirection;
	char	**split_again;
	char	**args;
}				t_red_struct;

typedef struct  s_cmd_struct
{
	int			n;
	int			no_of_pipes;
	int			status;
	int			open;
	char		*s;
	char		*current;
	t_list		**lst_env;
	int			tfd_index[4];
	t_cmd		**tcmd;
	t_fds		tfd[10];
	t_red_struct	*trst;
	struct s_pipe		tpipe[10];
}               t_cmd_struct;

/* util */
int		get_closed_index(t_cmd_struct *tcst, int index);
int 	has_parenthesis(char *s);
char    *get_first_delimiter(char *s);
int		has_delimiter(char *s);
int		has_open_parenthesis(char *s);
int		has_close_parenthesis(char *s);
int		get_no_of_command(char *s);
void	copy_string(t_cmd **tcmd, char *src, int len);
void	copy_string_char(char **s, char *src, int len);
int		get_no_of_pipes(t_cmd_struct *tcst);
int		get_no_of_redirection(t_cmd *t);
int		get_length_of_args(char **split_arg);

/* init */
int		set_arguments(t_cmd *tcmd, t_cmd_struct *tcst);
void	init_tcst(t_cmd_struct **tcst, char *s, int status);
void	init_tcmd(t_cmd_struct *tcst);
void	init_pipe(t_cmd_struct *tcst);
void	init_env(t_list **lst_env);
void	show_env_list(t_list **lst_env);

/* pipe */
void	set_pipe_head(t_cmd_struct *tcst, int cmd_index);
void	set_pipe_body(t_cmd_struct *tcst, int cmd_index);
void	set_pipe_tail(t_cmd_struct *tcst, int cmd_index);


char	**ft_split_first(char const *s, char c);
char	**ft_split_string(char const *s, char *d);
char	**ft_split_quote(char const *s, char c);

char	*get_next_line(int fd);