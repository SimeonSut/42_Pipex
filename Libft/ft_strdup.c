/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                         :+:    :+:           */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 17:06:03 by ssutarmi          #+#    #+#             */
/*   Updated: 2025/11/27 15:03:53 by ssutarmi       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*duplicate;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s[i])
		i++;
	duplicate = malloc((i + 1) * sizeof(char));
	if (!duplicate)
		return (NULL);
	duplicate[i] = '\0';
	while (s[j])
	{
		duplicate[j] = s[j];
		j++;
	}
	return (duplicate);
}
