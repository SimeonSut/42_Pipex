/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putdec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 10:14:29 by ssutarmi          #+#    #+#             */
/*   Updated: 2025/10/24 17:35:09 by ssutarmi         ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putdec(int nb)
{
	long	n;
	int		count;

	n = nb;
	count = 0;
	if (n < 0)
	{
		count += ft_putchar('-');
		n = -n;
	}
	if (n > 9)
		count += ft_putdec(n / 10);
	count += ft_putchar(((n % 10) + 48));
	return (count);
}
