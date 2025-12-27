/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 20:58:58 by ssutarmi          #+#    #+#             */
/*   Updated: 2025/10/15 16:35:32 by ssutarmi         ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*ptr_dest;
	unsigned char	*ptr_src;

	ptr_src = (unsigned char *)src;
	ptr_dest = (unsigned char *)dest;
	if (!dest && !src)
		return (NULL);
	if (ptr_dest <= ptr_src)
		while (n--)
			*ptr_dest++ = *ptr_src++;
	else if (ptr_dest > ptr_src)
	{
		ptr_src += n - 1;
		ptr_dest += n - 1;
		while (n--)
			*ptr_dest-- = *ptr_src--;
	}
	return (dest);
}
