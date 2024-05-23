/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghyki <sunghyki@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 09:22:14 by sunghyki          #+#    #+#             */
/*   Updated: 2024/05/07 09:22:21 by sunghyki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"

static void	inner_main(t_cmd_struct *tcst, char *s)
{
	int	i;

	copy_string_char(tcst, &(tcst->s), s, ft_strlen(s));
	init_tcmd(tcst);
	tcst->no_of_pipes = get_no_of_pipes(tcst);
	main_check_pipe(tcst);
	i = -1;
	while (++i < tcst->no_of_pipes)
		close(tcst->tpipe[i].fd[1]);
}

int	main(void)
{
	t_cmd_struct	*tcst;
	t_list			**lst_env;
	int				status;
	char			*s;

	s = NULL;
	main_init(&status);
	lst_env = malloc (sizeof(t_list *));
	init_env(lst_env);
	while (1)
	{
		s = readline("minishell $ ");
		if (s == 0)
			exit(0);
		if (is_empty_command(s[0]) || has_only_spaces(s) \
				|| is_empty_string(s) == 1)
			continue ;
		add_history(s);
		init_tcst(&tcst, s, status);
		tcst->lst_env = lst_env;
		inner_main(tcst, s);
		status = free_all(tcst);
	}
}
