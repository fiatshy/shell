/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghyki <sunghyki@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 09:45:43 by sunghyki          #+#    #+#             */
/*   Updated: 2024/05/21 09:56:14 by sunghyki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/wait.h>
# include <signal.h>
# include <stdio.h>
# include <stdbool.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/stat.h>
# include <dirent.h>
# include <sys/types.h>
# include "libft.h"
# include "get_next_line.h"

typedef struct s_cmd
{
	char	*cmd;
	char	**arg;
	char	**env;
	char	*next_delimiter;
	bool	execute;
	int		open;
	int		close;
	int		no_of_redirection;
	int		pipe_index;
}		t_cmd;

typedef struct s_split
{
	size_t	i;
	size_t	j;
	size_t	idx;
	bool	quote;
}				t_split;

typedef struct s_first
{
	size_t	i;
	size_t	j;
	size_t	idx;
	bool	quote;
	bool	first;
}				t_first;

typedef struct s_str
{
	size_t	i;
	size_t	j;
	size_t	idx;
	char	*operand;
}			t_str;

typedef struct s_pipe
{
	int	fd[2];
}		t_pipe;

typedef struct s_fds
{
	int	write;
	int	read;
	int	append;
	int	tmp;
}				t_fds;

typedef struct s_red_struct
{
	char	**split_redirection;
	char	**split_again;
	char	**args;
}				t_red_struct;

typedef struct s_cmd_struct
{
	int				n;
	int				no_of_pipes;
	int				status;
	int				open;
	char			*s;
	char			*current;
	t_list			**lst_env;
	int				tfd_index[4];
	t_cmd			**tcmd;
	t_fds			tfd[10];
	t_red_struct	*trst;
	struct s_pipe	tpipe[10];
}		t_cmd_struct;

typedef struct s_var
{
	int	k;
	int	length;
}				t_var;

/* pipe */
void	set_pipe_head(t_cmd_struct *tcst);
void	set_pipe_body(t_cmd_struct *tcst, int cmd_index);
void	set_pipe_tail(t_cmd_struct *tcst);

/* ft_split_first */
void	count_words_first_nested(const char *s, int i, bool *quote);
size_t	count_words_first(char const *s, char c);
int		has_delimiter_first(char s);
int		count_length_first_nested(char const *s, \
			size_t *i, size_t *j, bool *first);
size_t	count_length_first(char const *s, size_t *i, bool *first);
void	init_first(t_first *tf);
char	**split_arr_first(char **split, char const *s);
char	**ft_split_first(char const *s);

/* ft_split_quote */
void	count_quote_nest_in_nest(size_t *words, \
		char const *s, size_t *i, char c);
void	count_quote_nested(char c, char const *s, size_t *i, size_t *words);
size_t	count_words_quote(char const *s, char c);
void	count_length_quote_nested(char const *s, size_t *i, char *c, size_t *j);
size_t	count_length_quote(char const *s, char c, size_t *i);
char	**split_arr_quote(char **split, char const *s, char c);
char	**ft_split_quote(char const *s, char c);

/* ft_split_string */
int		has_delimiters(const char *s, const char *d);
size_t	count_words_string(char const *s, char *c);
size_t	count_length_string(char const *s, char *c, size_t *i);
char	*split_routine(size_t *i, char const *s, size_t *j, char *operand);
void	init_string(t_str *ts);
char	**split_arr_string(char **split, char const *s, char *c);
char	**ft_split_string(char const *s, char *d);

/* arg_dollar_check */
int		has_double_quote(char *split_arg);
int		is_double_is_outer(char *split_arg);
int		has_dollar(char *split_arg);
int		space_after_dollar(char *string);

/* arg_dollar_environ */
void	split_envirion_nested(char *string, int idx, char temp[4][100]);
void	split_environ(char *string, char temp[4][100]);
void	free_env_input(char **split_env_input);

/* arg_dollar_set */
void	handle_flag(char **split_arg, int i);
void	handle_dollar_nested(char split_env[4][100], \
	char **split_arg, int i, t_cmd_struct *tcst);
void	handle_dollar(char **split_arg, int i, t_cmd_struct	*tcst);
void	handle_dollar_compare(char split_env[4][100], \
	char **split_arg, int i, char **split_env_input);

/* arg_wild_check */
int		has_asterisk(char *s);
int		process_wildcard(char *f, char *t);
int		how_much_files(char	*target);

/* arg_wild_set */
void	opendir_args(DIR **dp, struct dirent **entry);
char	**split_args(char *s, int length);
char	**split_asterisk(char *s);

/* arg_dollar_utils */
int		have_quote(char *s);
int		have_dollar_nonzero(char *s);
void	free_noquote_dollar(char **split_env);
void	noquote_nested(char **s, t_list *temp);
void	make_blank_string(char **s);

/*arg_question_set*/
void	make_question_mark(char **s);
int		handle_question(char **s);
void	handle_noquote_dollar(char **s, t_cmd_struct *tcst);
int		has_expr(char *s);

/*arg_set*/
void	set_arguments_nested(t_cmd *tcmd, int i, \
	t_cmd_struct *tcst, char **split_arg);
int		set_arguments(t_cmd *tcmd, t_cmd_struct *tcst);

/*init*/
void	init_tcst(t_cmd_struct **tcst, char *s, int status);
void	init_tcmd_set_openclose(t_cmd_struct *tcst, char **split, int i);
void	init_tcmd(t_cmd_struct *tcst);
void	free_init_tcmd(char **split, char *trim_str);

/*init_fd_pipe*/
void	init_fds(t_cmd_struct *tcst);
void	set_pipe_index(t_cmd_struct *tcst, int i);
void	nested_pipe_index(t_cmd_struct *tcst, int i);
void	init_pipe(t_cmd_struct *tcst);

/* init_env */
void	show_env_list(t_list **lst_env);
void	init_env(t_list **lst_env);

/* gen_next_line */
char	*get_next_line(int fd);

/* handle_parenthesis */
int		has_parenthesis(char *s);
char	*get_first_delimiter(char *s);
int		has_delimiter(char *s);
int		has_open_parenthesis(char *s);
int		has_close_parenthesis(char *s);

/* util_gets */
int		get_closed_index(t_cmd_struct *tcst, int index);
int		get_no_of_command(char *s);
int		get_no_of_pipes(t_cmd_struct *tcst);
int		get_no_of_redirection(t_cmd *t);
int		get_length_of_args(char **split_arg);

/* util */
void	copy_string(t_cmd **tcmd, char *src, int len);
void	copy_string_char(t_cmd_struct *tcst, char **s, char *src, int len);
void	check_redirection(char **s, bool *quote, int *count);
void	main_check_pipe(t_cmd_struct *tcst);
void	main_init(int *status);

/* handle_signal */
void	handle_interrupt(int signo);
void	handle_interrupt_blocked(int signo);
int		check_if_ctrl_d(char *s);

/* set_tunnel */
char	*make_bin(t_cmd_struct *tcst);
void	init_dup2(t_cmd_struct *tcst);
void	close_fds(t_cmd_struct *tcst);
void	set_tunnel_redirect(t_cmd_struct *tcst, int index);
void	set_tunnels(t_cmd_struct *tcst, int index);

/* env */
char	*get_env(void);
char	**get_envv(t_cmd_struct *tcst);

/* get_exec_path */
void	fork_and_exectue_nested(t_cmd_struct *tcst, int index);
void	get_execute_path_nested(int *response, \
		char *s, char **cmd_path, t_cmd_struct *tcst);
char	*get_exectue_path(char *s, t_cmd_struct *tcst);

/* builtin */
void	ft_echo(t_cmd_struct *tcst, int index);
void	ft_exit(void);
void	ft_status(t_cmd_struct *tcst);
void	ft_pwd(void);

/* relative utils */
int		find_slash_reverse(char *s, int target);
void	copy_path(char temp[255], char *src);
int		has_relative_path(char *s);
int		has_multi_dots(char *s);

/* relative_path*/
char	*extract_command(t_cmd_struct *tcst, int index);
void	delete_redundant_path(char temp[255], int start);
char	*relative_path_exec_nested(char cwd[255]);
char	*get_relative_path(t_cmd_struct *tcst, int index);
char	*get_relative_path_exec(t_cmd_struct *tcst, int index);

/*builtin nested*/
void	ft_cd(t_cmd_struct *tcst, int index);
int		ft_env(t_cmd_struct *tcst);
void	ft_export(t_cmd_struct *tcst, int index);
void	ft_unset(t_cmd_struct *tcst, int index);

/* builtin utils */
int		is_builtin(t_cmd_struct *tcst, int index);
int		exec_builtin(t_cmd_struct *tcst, int index);

/* misc */
void	trim(t_cmd_struct *tcst, int index, int i);
char	*what_quotes(char *s);
void	get_file_length(int *i);
void	write_env(char **arr, t_cmd_struct *tcst, int index);
int		is_empty_string(char *s);

/* fork parents */
int		handle_res_nested(int *res, t_cmd_struct *tcst, int index);
int		handle_res(int *res, t_cmd_struct *tcst, int index);
void	handle_parent(t_cmd_struct *tcst);

/* fork */
void	fork_nested(int res, t_cmd_struct *tcst, int index);
void	fork_and_exectue_nested(t_cmd_struct *tcst, int index);
int		fork_and_execute(t_cmd_struct *tcst, int index);

/* grouping */
int		check_grouping_or(t_cmd_struct *tcst, int *i, int *proceed);
int		check_grouping_and(t_cmd_struct *tcst, int *i, int *proceed);
int		check_grouping(t_cmd_struct *tcst, int *i, int *proceed);

/* free */
int		free_all(t_cmd_struct *tcst);
void	free_after_exectue(t_cmd_struct *tcst, int i, int *proceed);
void	free_redirection(t_cmd_struct *tcst, int j);
void	free_again(t_cmd_struct *tcst, int k);
int		free_redirect_all(t_cmd_struct *tcst);

/* fork redirect */
void	set_redirect_args(t_cmd_struct *tcst, int *index, int k);
void	handle_redirect_delim_nested(t_cmd_struct *tcst, int k);
void	handle_redirect_delim(t_cmd_struct *tcst, int k);
void	handle_redirect_output(t_cmd_struct *tcst, int k);
void	handle_again(t_cmd_struct *tcst, int k, int *index);

/* fork_redirection_nested */
void	redirect_parents(t_cmd_struct *tcst, int index);
void	execute_redirection(t_cmd_struct *tcst, int index);
int		get_args_length(char **s);
int		handle_redirection_nested(t_cmd_struct *tcst, int j);
int		handle_redirection(t_cmd_struct *tcst, int i);

/* fork_prepare */
int		prepare_execute_nested(t_cmd_struct *tcst, \
			int i, int proceed, int cont);
int		prepare_execute(t_cmd_struct *tcst);
int		has_only_spaces(char *s);
int		is_empty_command(char s);
int		check_wrong_redirection(char *s);

#endif
