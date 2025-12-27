/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 16:55:59 by ssutarmi          #+#    #+#             */
/*   Updated: 2025/10/28 13:22:56 by ssutarmi         ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	ft_separate(char const *str, char c)
{
	unsigned int	count;

	count = 0;
	while (*str && *str != c)
	{
		str++;
		count++;
	}
	return (count);
}

static size_t	ft_splitcount(char const *str, char c)
{
	size_t	count;

	count = 0;
	while (*str)
	{
		if (*str != c)
		{
			count++;
			str += ft_separate(str, c);
		}
		else
			str++;
	}
	return (count);
}

static void	*ft_remove(char **result)
{
	unsigned int	i;

	i = 0;
	while (result[i])
		free(result[i++]);
	free(result);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	unsigned int	pos;
	char			**result;

	pos = 0;
	if (!s)
		return (NULL);
	result = (char **)ft_calloc(ft_splitcount(s, c) + 1, sizeof(char *));
	if (!result)
		return (NULL);
	while (*s)
	{
		if (*s != c)
		{
			result[pos] = ft_substr(s, 0, ft_separate(s, c));
			if (!result[pos++])
				return (ft_remove(result));
			s += ft_separate(s, c);
		}
		else
			s++;
	}
	return (result);
}
