/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 16:34:34 by ssutarmi          #+#    #+#             */
/*   Updated: 2025/10/24 17:35:57 by ssutarmi         ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putptr(void	*s)
{
	int	i;

	if (s == NULL)
		return (ft_putstr("(nil)"));
	i = ft_putstr("0x");
	i += ft_puthexap((unsigned long long)s, "0123456789abcdef");
	return (i);
}
