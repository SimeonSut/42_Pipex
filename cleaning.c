/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <ssutarmi@student_42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 13:41:19 by ssutarmi          #+#    #+#             */
/*   Updated: 2026/01/14 16:08:45 by ssutarmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free_chain(t_pipe *head)
{
	t_pipe	*track;

	while (head)
	{
		track = head->next;
		free_table(head->cmd_args);
		free(head);
		head = track;
	}
	return ;
}
