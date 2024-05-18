/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghyki <sunghyki@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:53:59 by sunghyki          #+#    #+#             */
/*   Updated: 2024/05/16 17:54:00 by sunghyki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_test.h"

void	show_env_list(t_list **lst_env)
{
	t_list	*temp;

	temp = *lst_env;
	while (temp)
	{
		printf("%s\n", (char *)temp->content);
		temp = temp->next;
	}
}

void	init_env(t_list **lst_env)
{
	extern char	**environ;

	*lst_env = ft_lstnew(*environ);
	while (*environ)
		ft_lstadd_back(lst_env, ft_lstnew(*environ++));
}
