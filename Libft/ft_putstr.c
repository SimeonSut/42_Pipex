/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 16:09:56 by ssutarmi          #+#    #+#             */
/*   Updated: 2025/10/24 17:36:13 by ssutarmi         ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr(char *str)
{
	int	i;

	if (!str)
		return (ft_putstr("(null)"));
	i = ft_strlen(str);
	while (*str)
		ft_putchar_fd(*str++, 1);
	return (i);
}
