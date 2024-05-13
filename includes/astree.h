/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astree.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonhseo <wonhseo@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 04:57:08 by wonhseo           #+#    #+#             */
/*   Updated: 2024/05/14 06:42:42 by wonhseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASTREE_H
# define ASTREE_H
# include "rbtree.h"
# include "libft.h"
# define AASSERT			"Assertion failed: "
# define ROLLBACK			"function rollback, "
# define AS_EXEC			"funciton as_exec, "
# define AS_INIT			"function as_init, "
# define AEXEC_FILE			"file astree/exec.c, "
# define AFRAG_1_FILE		"file astree/frag_1.c, "
# define SYNTAX				"Syntax error"
# define HEREDOC			".heredoc"

typedef void	(*t_as_exec_fn)();
typedef struct s_as
{
	bool			root;
	bool			heredoc;
	char			*token;
	t_type			type;
	t_as_exec_fn	exec;
	struct s_as		*left;
	struct s_as		*right;
}					t_as;
void	as_assert(bool condition, char *context);
bool	as_check(t_as *syntax);
void	as_exec(t_as *syntax, t_rb *envmap);
t_as	*as_init(t_lst *chunks);
t_as	*make_frag(t_lst *chunk);
t_as	*as_insert(t_as *syntax, t_as *frag);
void	as_free(t_as *syntax);
void	as_syntax(t_as *syntax, int level);
void	as_print(t_as *syntax);
#endif
