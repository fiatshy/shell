/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonhseo <wonhseo@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 04:59:47 by wonhseo           #+#    #+#             */
/*   Updated: 2024/05/14 04:59:47 by wonhseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_lst	*ft_lstmap(t_lst *lst, void *(*f)(void *), void (*del)(void **))
{
	t_lst	*new;
	t_lst	*buf;
	t_lst	*tmp;

	tmp = NULL;
	if (!lst || !f)
		return (NULL);
	new = ft_lstnew(f(lst->content));
	if (!new)
		return (NULL);
	buf = new;
	lst = lst->next;
	while (lst)
	{
		tmp = ft_lstnew(f(lst->content));
		if (!tmp)
		{
			ft_lstclear(&new, del);
			return (NULL);
		}
		buf->next = tmp;
		buf = tmp;
		lst = lst->next;
	}
	return (new);
}
