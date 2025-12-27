/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 15:33:50 by ssutarmi          #+#    #+#             */
/*   Updated: 2025/10/15 16:46:34 by ssutarmi         ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*substr;

	if (!s)
		return (NULL);
	i = ft_strlen(s);
	if (start >= i)
		return (ft_strdup(""));
	if (start + len > i)
		len = i - start;
	substr = ft_calloc(len + 1, sizeof(char));
	if (!substr)
		return (NULL);
	i = 0;
	while (i < len)
	{
		substr[i] = s[start];
		i++;
		start++;
	}
	return (substr);
}
