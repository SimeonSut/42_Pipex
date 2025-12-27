/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 12:52:38 by ssutarmi          #+#    #+#             */
/*   Updated: 2025/10/15 16:28:13 by ssutarmi         ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	result;
	int	sign;

	result = 0;
	sign = 1;
	while ((*nptr > 8 && *nptr < 14) || *nptr == 32)
		nptr++;
	if (*nptr == 43 || *nptr == 45)
	{
		if (*nptr == 45)
			sign = -1;
		nptr++;
	}
	while (*nptr > 47 && *nptr < 58)
	{
		result *= 10;
		result += (*nptr - 48);
		nptr++;
	}
	return ((result * sign));
}
