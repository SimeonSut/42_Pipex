/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 15:33:50 by ssutarmi          #+#    #+#             */
/*   Updated: 2025/10/13 17:05:06 by ssutarmi         ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	nb;

	nb = n;
	if (nb < 0)
	{
		ft_putchar_fd('-', fd);
		nb = -nb;
	}
	if (nb > 9)
	{
		ft_putnbr_fd(nb / 10, fd);
	}
	ft_putchar_fd((nb % 10) + 48, fd);
}
