/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 16:35:47 by ssutarmi          #+#    #+#             */
/*   Updated: 2025/10/13 19:37:13 by ssutarmi         ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*ptr;
	size_t			i;

	i = 0;
	ptr = (unsigned char *) malloc((nmemb * size));
	if (!ptr)
		return (NULL);
	while (i < (nmemb * size))
	{
		ptr[i] = '\0';
		i++;
	}
	return ((void *)ptr);
}
