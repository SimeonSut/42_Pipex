/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthexa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 18:29:04 by ssutarmi          #+#    #+#             */
/*   Updated: 2025/10/24 17:35:22 by ssutarmi         ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_puthexa(unsigned int nbr, char *base)
{
	int		count;
	char	c;

	count = 1;
	if (nbr >= 16)
		count += ft_puthexa(nbr / 16, base);
	c = base[nbr % 16];
	ft_putchar_fd(c, 1);
	return (count);
}
