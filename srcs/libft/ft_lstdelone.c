/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonhseo <wonhseo@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 04:59:38 by wonhseo           #+#    #+#             */
/*   Updated: 2024/05/14 04:59:38 by wonhseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_lst *lst, void (*del)(void **))
{
	if (!lst)
		return ;
	if (del)
		del(&(lst->content));
	ft_free((void **)(&lst));
}
