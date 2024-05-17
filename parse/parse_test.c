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
#include "parse_test.h"

int	main(void)
{
	t_cmd_struct	*tcst;
	t_list			**lst_env;
	int				status;
	char			*s;

	status = 0;
	lst_env = malloc (sizeof(t_list *));
	init_env(lst_env);
	signal(SIGINT, handle_interrupt);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		s = readline("shell $ ");
		if (s == 0)
			exit(0);
		if (is_empty_command(s[0]) || has_only_spaces(s))
			continue ;
		add_history(s);
		init_tcst(&tcst, s, status);
		tcst->lst_env = lst_env;
		copy_string_char(tcst, &(tcst->s), s, ft_strlen(s));
		init_tcmd(tcst);
		tcst->no_of_pipes = get_no_of_pipes(tcst);
		if (tcst->no_of_pipes <= 5)
		{
			init_pipe(tcst);
			prepare_execute(tcst);
			signal(SIGINT, handle_interrupt);
			signal(SIGQUIT, SIG_IGN);
		}
		else
			printf("too many pipes\n");
		status = free_all(tcst);
	}
}
