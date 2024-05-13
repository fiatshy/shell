/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonhseo <wonhseo@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 05:01:53 by wonhseo           #+#    #+#             */
/*   Updated: 2024/05/14 06:46:26 by wonhseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_lst	*chunks;
	t_as	*syntax;
	t_rb	*envmap;

	input = NULL;
	chunks = NULL;
	syntax = NULL;
	envmap = rb_init(rb_compare);
	set_signal(customized, SIG_IGN);
	echoctl_off();
	pair(argc, argv, envp, envmap);
	loop(input, chunks, syntax, envmap);
	return (VALID);
}
