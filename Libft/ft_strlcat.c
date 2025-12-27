/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 15:54:11 by ssutarmi          #+#    #+#             */
/*   Updated: 2025/10/15 16:42:14 by ssutarmi         ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dlen;
	size_t	slen;
	size_t	cat;
	size_t	sum;

	dlen = ft_strlen(dst);
	slen = ft_strlen(src);
	cat = 0;
	sum = 0;
	if (size > dlen)
		sum = (dlen + slen);
	else
		return (size + slen);
	while (dlen + 1 < size && src[cat])
	{
		dst[dlen] = src[cat];
		dlen++;
		cat++;
	}
	dst[dlen] = '\0';
	return (sum);
}
