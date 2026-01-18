/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <ssutarmi@student_42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 13:41:19 by ssutarmi          #+#    #+#             */
/*   Updated: 2026/01/18 15:44:29 by ssutarmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_chain(t_pipe *head)
{
	while (head)
		head = free_node(head);
}

t_pipe	*free_node(t_pipe *node)
{
	t_pipe	*track;

	track = node->next;
	free(node->pathname);
	if (node->arguments)
		free_table(node->arguments);
	free(node);
	return (track);
}
