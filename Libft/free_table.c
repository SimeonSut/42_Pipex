/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   free_table.c                                        :+:    :+:           */
/*                                                      +:+                   */
/*   By: ssutarmi <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2026/01/16 20:59:47 by ssutarmi       #+#    #+#                */
/*   Updated: 2026/01/16 20:59:48 by ssutarmi       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_table(char **table)
{
	int	i;

	i = 0;
	while (table[i])
		free(table[i++]);
	free(table);
}
