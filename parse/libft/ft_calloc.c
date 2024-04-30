/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghyki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 12:03:31 by sunghyki          #+#    #+#             */
/*   Updated: 2024/03/06 19:10:04 by sunghyki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	if (!nmemb || !size || (nmemb * size) == 0)
	{
		ptr = (void *) malloc (nmemb * size);
		return (ptr);
	}
	if ((nmemb * size) / size != nmemb)
		return (NULL);
	ptr = (void *) malloc (nmemb * size);
	if (ptr == 0)
		return (NULL);
	ft_bzero(ptr, nmemb * size);
	return (ptr);
}
