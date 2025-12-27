/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 12:53:46 by ssutarmi          #+#    #+#             */
/*   Updated: 2025/10/15 16:45:28 by ssutarmi         ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		index;
	char	*str;

	index = 0;
	str = (char *)s;
	while (str[index])
		index++;
	while (index >= 0)
	{
		if (str[index] == (unsigned char)c)
			return (&str[index]);
		index--;
	}
	return (NULL);
}
