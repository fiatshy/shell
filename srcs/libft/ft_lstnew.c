/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonhseo <wonhseo@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 04:59:50 by wonhseo           #+#    #+#             */
/*   Updated: 2024/05/14 04:59:50 by wonhseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_lst	*ft_lstnew(void *content)
{
	t_lst	*tmp;

	if (!ft_calloc((void **)(&tmp), 1, sizeof(t_lst)))
		return (NULL);
	tmp->content = content;
	tmp->next = NULL;
	return (tmp);
}
