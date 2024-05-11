/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghyki <sunghyki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 11:51:27 by sunghyki          #+#    #+#             */
/*   Updated: 2024/03/03 11:51:28 by sunghyki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void	*content)
{
	t_list	*temp;

	temp = (t_list *) malloc (sizeof(t_list));
	if (temp == 0)
		return (0);
	//temp->content = content;
	temp->content = malloc (ft_strlen((const char *)content) + 1);
	ft_memcpy(temp->content, content, ft_strlen((const char *)content) + 1);
	//temp->content[ft_strlen((const char *)content)] = 0;
	temp->next = 0;
	return (temp);
}
