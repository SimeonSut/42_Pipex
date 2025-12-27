/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   ft_atol.c                                           :+:    :+:           */
/*                                                      +:+                   */
/*   By: ssutarmi <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/12/01 18:04:45 by ssutarmi       #+#    #+#                */
/*   Updated: 2025/12/01 18:09:34 by ssutarmi       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

long	ft_atol(const char *nptr)
{
	long	result;
	int		sign;

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
