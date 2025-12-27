/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 18:03:34 by ssutarmi          #+#    #+#             */
/*   Updated: 2025/10/15 16:35:06 by ssutarmi         ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*ptr_dest;
	unsigned char	*ptr_src;

	if (!dest && !src)
		return (NULL);
	ptr_src = (unsigned char *)src;
	ptr_dest = (unsigned char *)dest;
	while (n-- > 0)
		*(ptr_dest++) = *(ptr_src++);
	return (dest);
}
