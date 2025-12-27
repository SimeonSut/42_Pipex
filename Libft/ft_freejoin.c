/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freejoin.c                                       :+:    :+:           */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 15:22:54 by ssutarmi          #+#    #+#             */
/*   Updated: 2025/11/27 15:21:06 by ssutarmi       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_freejoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*s3;

	i = 0;
	j = 0;
	while (s1[i])
		i++;
	while (s2[j])
		j++;
	if (i == 0 && j == 0)
		return (free(s1), free(s2), NULL);
	else if (i == 0 && j != 0)
		return (free(s1), s2);
	else if (j == 0 && i != 0)
		return (free(s2), s1);
	s3 = malloc((i + j + 1) * sizeof(char));
	if (!s3)
		return (free(s1), free(s2), NULL);
	s3[i + j] = '\0';
	while (j--)
		s3[i + j] = s2[j];
	while (i--)
		s3[i] = s1[i];
	return (free(s1), free(s2), s3);
}
