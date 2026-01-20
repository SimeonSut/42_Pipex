/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <ssutarmi@student_42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 13:41:19 by ssutarmi          #+#    #+#             */
/*   Updated: 2026/01/20 22:25:06 by ssutarmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_chain(t_pipe *head)
{
	t_pipe	*track;

	while (head)
	{
		track = head->next;
		if (head->pathname)
			free(head->pathname);
		if (head->arguments)
			free_table(head->arguments);
		free(head);
		head = track;
	}
}
