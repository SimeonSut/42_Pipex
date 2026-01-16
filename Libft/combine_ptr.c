/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   combine_ptr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <ssutarmi@student_42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 20:45:19 by ssutarmi          #+#    #+#             */
/*   Updated: 2026/01/16 21:44:32 by ssutarmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**combine_ptr(int count, ...)
{
	va_list	list;
	int		i;
	char	*str;
	char	**result;

	result = malloc((count + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	result[count] = NULL;
	i = 0;
	va_start(list, count);
	while (count-- > 0)
		result[i++] = ft_strdup(va_arg(list, char *));
	va_end(list);
	return (result);
}
