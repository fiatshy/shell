/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghyki <sunghyki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 11:52:06 by sunghyki          #+#    #+#             */
/*   Updated: 2024/03/03 11:52:07 by sunghyki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*save;

	if (lst && del)
	{
		while (*lst)
		{
			save = (*lst)->next;
			ft_lstdelone(*lst, del);
			*lst = save;
		}
		*lst = 0;
	}
}
