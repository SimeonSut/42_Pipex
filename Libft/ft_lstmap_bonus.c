/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 15:39:00 by ssutarmi          #+#    #+#             */
/*   Updated: 2025/10/15 16:53:32 by ssutarmi         ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*start;
	void	*tmp;

	if (!f || !del)
		return (NULL);
	start = NULL;
	while (lst)
	{
		tmp = f(lst->content);
		new = ft_lstnew(tmp);
		if (!new)
		{
			ft_lstclear(&start, del);
			del(tmp);
			return (0);
		}
		ft_lstadd_back(&start, new);
		lst = lst->next;
	}
	return (start);
}
