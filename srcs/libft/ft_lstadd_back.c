/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonhseo <wonhseo@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 04:59:29 by wonhseo           #+#    #+#             */
/*   Updated: 2024/05/14 04:59:29 by wonhseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_lst **lst, t_lst *new_node)
{
	t_lst	*tmp;

	if (!lst || !new_node)
		return ;
	if (!*lst)
		*lst = new_node;
	else
	{
		tmp = ft_lstlast(*lst);
		tmp->next = new_node;
	}
}
