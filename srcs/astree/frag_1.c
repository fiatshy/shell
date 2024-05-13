/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frag_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonhseo <wonhseo@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 04:57:43 by wonhseo           #+#    #+#             */
/*   Updated: 2024/05/14 06:45:05 by wonhseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "astree.h"
#include "minishell.h"

t_as	*as_init(t_lst *chunks)
{
	t_as	*syntax;
	t_as	*frag;

	syntax = NULL;
	while (chunks != NULL)
	{
		frag = make_frag(chunks);
		as_assert(frag != NULL, \
			AASSERT "(frag != NULL), " AS_INIT AFRAG_1_FILE "line 33.");
		syntax = as_insert(syntax, frag);
		chunks = chunks->next;
	}
	syntax->root = true;
	return (syntax);
}

static inline void	identity(t_as *frag, t_type type, char heredoc)
{
	extern void	exec_rdr(t_as	*syntax, t_rb *envmap);
	extern void	exec_pipe(t_as	*syntax, t_rb *envmap);
	extern void	exec_cmd(t_as	*syntax, t_rb *envmap);

	frag->type = type;
	if (type == RDR)
		frag->exec = exec_rdr;
	else if (type == PIPE)
		frag->exec = exec_pipe;
	else
		frag->exec = exec_cmd;
	if (heredoc == '<')
		frag->heredoc = true;
	else
		frag->heredoc = false;
}

t_as	*make_frag(t_lst *chunk)
{
	t_as	*frag;
	char	*data;

	data = (char *)(chunk->content);
	if (!ft_calloc((void **)(&frag), 1, sizeof(t_as)))
		return (NULL);
	if (!ft_strncmp(">", data, BUFFER_SIZE) || !ft_strncmp(">>", data,
			BUFFER_SIZE) || !ft_strncmp("<", data, BUFFER_SIZE)
		|| !ft_strncmp("<<", data, BUFFER_SIZE))
		identity(frag, RDR, *(data + 1));
	else if (!ft_strncmp("|", data, BUFFER_SIZE))
		identity(frag, PIPE, 0);
	else
		identity(frag, CMD, 0);
	frag->root = false;
	frag->token = data;
	frag->left = NULL;
	frag->right = NULL;
	return (frag);
}
