/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghyki <sunghyki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 11:51:19 by sunghyki          #+#    #+#             */
/*   Updated: 2024/03/03 11:51:21 by sunghyki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	unsigned int	lst_size;

	lst_size = 1;
	if (!lst)
		return (0);
	while (lst->next)
	{
		lst = lst->next;
		lst_size++;
	}
	return (lst_size);
}
