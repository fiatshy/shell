/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonhseo <wonhseo@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 04:57:28 by wonhseo           #+#    #+#             */
/*   Updated: 2024/05/14 06:42:52 by wonhseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "astree.h"
# include "libft.h"
# include <stdbool.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/stat.h>
# include <termios.h>
# include <readline/history.h>
# include <readline/readline.h>
# define MASSERT			"Assertion failed: "
# define IS_BUILTIN			"function is_builtin, "
# define BINARY_INTERNAL	"function binary_internal, "
# define STRETCH			"function stretch, "
# define ACCUMULATE			"function accumulate, "
# define OUT_PROCESS		"function out_process, "
# define IN_PROCESS			"function in_process, "
# define EXEC_PIPE			"function exec_pipe, "
# define EXEC_RDR_GT		"function exec_rdr_gt, "
# define EXEC_RDR_LT		"function exec_rdr_lt, "
# define EXEC_RDR_RSHIFT	"function exec_rdr_rshift, "
# define EXEC_RDR_LSHIFT	"function exec_rdr_lshift, "
# define EXPAND_SPACE		"function expand_space, "
# define EXPAND_BRACE		"function expand_brace, "
# define EXPAND_MIDDLE		"function expand_middle, "
# define PAIR_ARGV			"function pair_argv, "
# define TOKENIZE_INTERNAL	"function tokenize_internal, "
# define LOOP				"function loop, "
# define MCOMMAND_1_FILE	"file exec/command_1.c, "
# define MCOMMAND_2_FILE	"file exec/command_2.c, "
# define MPIPE_FILE			"file exec/pipe.c, "
# define MRDR_2_FILE		"file exec/rdr_2.c, "
# define MEXPAND_1_FILE		"file parse/expand_1.c, "
# define MPAIR_FILE			"file parse/pair.c, "
# define MTOKENIZE_FILE		"file parse/expand_1.c, "
# define MLOOP_FILE			"file runtime/loop.c, "
# define QUOTES				"Quotes not paired"
# define COMMANDS			"Command not found"
# define ENTRIES			"No such file or directory"
# define IDENTIFIER			"Not a valid identifier"
# define NUMERIC			"Numeric arguments required"
# define PERMISSIONS		"Permission denied"
# define SEVERAL			"Too many arguments"

int		builtin_cd(char **args, t_rb *envmap);
int		builtin_echo(char **args);
int		builtin_env(t_rb *envmap);
int		builtin_exit(char **args);
int		builtin_export(char **args, t_rb *envmap);
int		builtin_pwd(void);
int		builtin_unset(char **args, t_rb *envmap);
void	arrange(char *chunk);
char	**capture(t_as *syntax);
void	configure(char ***envp, t_node *node);
void	delete(char ***args);
char	*find(char *command, t_rb *envmap);
char	*resolve(char *input, t_rb *envmap);
void	exec_cmd(t_as *syntax, t_rb *envmap);
void	exec_pipe(t_as *syntax, t_rb *envmap);
void	exec_rdr_gt(t_as *syntax);
bool	exec_rdr_lt(t_as *syntax, t_rb *envmap);
void	exec_rdr_rshift(t_as *syntax);
void	exec_rdr_lshift(t_as *syntax, t_rb *envmap);
void	exec_rdr(t_as *syntax, t_rb *envmap);
char	*expand(char *input, t_rb *envmap, bool d_quote);
char	*expand_internal(char *input, char *iter, t_rb *envmap, bool d_quote);
void	pair(int argc, char **argv, char **envp, t_rb *envmap);
void	tokenize(char *input, t_lst **chunks);
char	*tokenize_internal(char *input, char *begin, char *end, t_lst **chunks);
void	mini_assert(bool condition, char *context);
bool	empty(char *input);
bool	quotes(char *cmd);
void	loop(char *input, t_lst *chunks, t_as *syntax, t_rb *envmap);
void	finish(char *entry, bool shutdown);
bool	set_rl(char *in, char *out, int fd, bool newline);
void	customized(int sig);
void	set_signal(void (*action1)(int), void (*action2)(int));
void	echoctl_on(void);
void	echoctl_off(void);
#endif
