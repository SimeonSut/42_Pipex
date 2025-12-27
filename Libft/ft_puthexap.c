/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthexap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 15:04:01 by ssutarmi          #+#    #+#             */
/*   Updated: 2025/10/24 17:35:39 by ssutarmi         ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_puthexap(unsigned long long nbr, char *base)
{
	int		count;
	char	c;

	count = 1;
	if (nbr < 0)
	{
		nbr = -nbr;
		ft_putchar_fd('-', 1);
	}
	if (nbr >= 16)
		count += ft_puthexap(nbr / 16, base);
	c = base[nbr % 16];
	ft_putchar_fd(c, 1);
	return (count);
}
