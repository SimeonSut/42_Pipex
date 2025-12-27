/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 13:47:08 by ssutarmi          #+#    #+#             */
/*   Updated: 2025/10/15 16:30:27 by ssutarmi         ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	ft_addnb(long n, int len)
{
	if (n < 0)
	{
		n = -n;
	}
	while (len > 1)
	{
		n /= 10;
		len--;
	}
	if (n > 9)
	{
		n %= 10;
		return (n + 48);
	}
	return (n + 48);
}

static long	ft_strcount(long n)
{
	int	count;

	count = 0;
	if (n < 0)
	{
		n = -n;
		count++;
	}
	while (n > 9)
	{
		n /= 10;
		count++;
	}
	count++;
	return (count);
}

char	*ft_itoa(int n)
{
	long	nb;
	int		i;
	int		len;
	char	*result;

	nb = n;
	i = 0;
	len = ft_strcount(nb);
	result = ft_calloc((len + 1), sizeof(char));
	if (!result)
		return (NULL);
	if (nb < 0)
	{
		result[i] = '-';
		i++;
	}
	while (i < len)
	{
		result[i] = ft_addnb(nb, len - i);
		i++;
	}
	return (result);
}
