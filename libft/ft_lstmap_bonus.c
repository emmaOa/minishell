/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouazzan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 01:52:55 by iouazzan          #+#    #+#             */
/*   Updated: 2021/11/26 01:53:01 by iouazzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	**index;
	t_list	*new;
	t_list	*temp;

	temp = lst;
	if (!lst)
		return (NULL);
	index = &new;
	while (temp)
	{
		new = ft_lstnew((f)(temp->content));
		if (!new)
		{
			ft_lstclear(index, del);
			return (NULL);
		}
		temp = temp->next;
		ft_lstadd_back(index, new);
	}
	return (new);
}
