#include <stdbool.h>

typedef struct	s_cmd
{
	char	*cmd;
	char	**arg;
	char	**env;
	int		arg_length;
	int		status;
	struct s_pipe *tp;
	struct s_parse *ts;
}				t_cmd;

typedef struct	s_pipe
{
	int	n;
	int	fd[2];
}				t_pipe;

typedef struct	s_parse
{
	char	**split_pipe;
	int		no_of_commands;
	int 	no_of_redirection;
	int		no_of_pipes;
	int		i;
	int		cmd_index;	
}				t_parse;

char	**ft_split_string(char const *s, char *d);
char	**ft_split_quote(char const *s, char c);