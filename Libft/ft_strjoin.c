/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 14:57:15 by ssutarmi          #+#    #+#             */
/*   Updated: 2025/11/08 12:21:14 by ssutarmi         ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*s3;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	i = ft_strlen(s1);
	j = ft_strlen(s2);
	s3 = ft_calloc(i + j + 1, sizeof(char));
	if (!s3)
		return (NULL);
	while (j-- > 0)
		s3[i + j] = s2[j];
	while (i-- > 0)
		s3[i] = s1[i];
	return (s3);
}
