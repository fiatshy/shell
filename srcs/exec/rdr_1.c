/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdr_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonhseo <wonhseo@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 04:58:36 by wonhseo           #+#    #+#             */
/*   Updated: 2024/05/14 04:58:36 by wonhseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_rdr(t_as *syntax, t_rb *envmap)
{
	bool	cont;

	cont = true;
	if (!ft_strncmp(syntax->token, ">", BUFFER_SIZE))
		exec_rdr_gt(syntax);
	else if (!ft_strncmp(syntax->token, "<", BUFFER_SIZE))
		cont = exec_rdr_lt(syntax, envmap);
	else if (!ft_strncmp(syntax->token, ">>", BUFFER_SIZE))
		exec_rdr_rshift(syntax);
	else if (!ft_strncmp(syntax->token, "<<", BUFFER_SIZE))
		exec_rdr_lshift(syntax, envmap);
	if (cont && syntax->right != NULL)
		syntax->right->exec(syntax->right, envmap);
}
