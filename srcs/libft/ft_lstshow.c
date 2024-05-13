/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstshow.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonhseo <wonhseo@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 04:59:53 by wonhseo           #+#    #+#             */
/*   Updated: 2024/05/14 04:59:54 by wonhseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstshow(t_lst *lst)
{
	if (!lst)
		return ;
	ft_putstr("\nList Size: ", STDOUT_FILENO);
	ft_putnbr(ft_lstsize(lst), STDOUT_FILENO);
	ft_putstr("\nList Elements: ", STDOUT_FILENO);
	while (lst)
	{
		ft_putstr((char *)(lst->content), STDOUT_FILENO);
		ft_putchar('\t', STDOUT_FILENO);
		lst = lst->next;
	}
	ft_putendl("\n", STDOUT_FILENO);
}
