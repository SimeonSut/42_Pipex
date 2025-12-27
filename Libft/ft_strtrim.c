/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 15:22:43 by ssutarmi          #+#    #+#             */
/*   Updated: 2025/10/15 16:46:04 by ssutarmi         ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	set_front(const char *s1, const char *set)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (*s1 && set[i])
	{
		while (*s1 == set[i])
		{
			s1++;
			count++;
			i = 0;
		}
		i++;
	}
	return (count);
}

size_t	set_back(const char *s1, const char *set)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (*s1)
		s1++;
	s1--;
	while (*s1 && set[i])
	{
		while (*s1 == set[i])
		{
			s1--;
			count++;
			i = 0;
		}
		i++;
	}
	return (count);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	start;
	size_t	len;
	char	*result;

	if (!*set)
		return (ft_strdup(s1));
	if (!s1 && !set)
		return (NULL);
	if (set_front(s1, set) == ft_strlen(s1))
		return (ft_strdup(""));
	i = ft_strlen(s1);
	start = (set_front(s1, set));
	len = (i - ((set_front(s1, set)) + set_back(s1, set)));
	result = (char *)ft_calloc((len + 1), sizeof(char));
	if (!result)
		return (NULL);
	i = 0;
	while (len--)
		result[i++] = s1[start++];
	return (result);
}
