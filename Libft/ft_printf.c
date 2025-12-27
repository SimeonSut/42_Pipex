/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 14:51:01 by ssutarmi          #+#    #+#             */
/*   Updated: 2025/10/24 17:34:43 by ssutarmi         ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_check(char ptr, va_list list, int i)
{
	if (ptr == 'd' || ptr == 'i')
		i += ft_putdec(va_arg(list, int));
	else if (ptr == 'u')
		i += ft_putun(va_arg(list, int));
	else if (ptr == 'x')
		i += ft_puthexa(va_arg(list, unsigned long long), "0123456789abcdef");
	else if (ptr == 'X')
		i += ft_puthexa(va_arg(list, unsigned long long), "0123456789ABCDEF");
	else if (ptr == 'c')
		i += ft_putchar(va_arg(list, int));
	else if (ptr == 's')
		i += ft_putstr(va_arg(list, char *));
	else if (ptr == 'p')
		i += ft_putptr(va_arg(list, void *));
	else if (ptr == '%')
		i += ft_putchar(37);
	return (i);
}

int	ft_printf(const char *ptr, ...)
{
	va_list	list;
	int		i;

	i = 0;
	va_start(list, ptr);
	while (*ptr)
	{
		if (*ptr == '%')
		{
			ptr++;
			i += ft_check(*ptr, list, 0);
		}
		else
		{
			ft_putchar_fd(*ptr, 1);
			i++;
		}
		ptr++;
	}
	va_end(list);
	return (i);
}
