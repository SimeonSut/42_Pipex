/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 12:53:15 by ssutarmi          #+#    #+#             */
/*   Updated: 2025/10/15 16:33:54 by ssutarmi         ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	unsigned char	unc;
	size_t			i;

	str = (unsigned char *)s;
	unc = (unsigned char) c;
	i = 0;
	while (i < n)
	{
		if (str[i] == unc)
			return ((void *)&str[i]);
		i++;
	}
	return (NULL);
}
