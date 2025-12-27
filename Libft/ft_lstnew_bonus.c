/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <ssutarmi@student_42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 09:18:25 by ssutarmi          #+#    #+#             */
/*   Updated: 2025/12/03 15:23:12 by ssutarmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*newnode;

	newnode = malloc(sizeof(t_list));
	if (!newnode)
		return (NULL);
	newnode->content = content;
	newnode->next = NULL;
	return (newnode);
}
