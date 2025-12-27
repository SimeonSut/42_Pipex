/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 17:46:17 by ssutarmi          #+#    #+#             */
/*   Updated: 2025/10/15 16:38:20 by ssutarmi         ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*str;

	str = (char *)s;
	while (*str)
	{
		if (*str == (unsigned char)c)
			return ((char *)str);
		str++;
	}
	if (*str == '\0' && (unsigned char)c == '\0')
		return ((char *)str);
	return (NULL);
}
