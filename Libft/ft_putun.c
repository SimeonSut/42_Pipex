/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putun.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 11:38:49 by ssutarmi          #+#    #+#             */
/*   Updated: 2025/10/24 17:36:28 by ssutarmi         ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_putposnbr(unsigned int n)
{
	if (n > 9)
		ft_putposnbr(n / 10);
	ft_putchar_fd((n % 10) + 48, 1);
}

static int	ft_count(unsigned int nb)
{
	unsigned int	count;
	unsigned int	n;

	count = 0;
	n = nb;
	if (n > 9)
	{
		while (n > 9)
		{
			n /= 10;
			count++;
		}
	}
	if (n >= 0 && n <= 9)
		count++;
	return (count);
}

int	ft_putun(int nb)
{
	ft_putposnbr(nb);
	return (ft_count(nb));
}
