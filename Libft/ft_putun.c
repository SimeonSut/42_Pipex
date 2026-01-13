/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putun.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <ssutarmi@student_42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 11:38:49 by ssutarmi          #+#    #+#             */
/*   Updated: 2026/01/13 17:42:43 by ssutarmi         ###   ########.fr       */
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
