/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 10:09:25 by lantonio          #+#    #+#             */
/*   Updated: 2025/01/11 10:09:26 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*aux;
	t_list	*temp;

	if (lst == NULL)
		return (NULL);
	new = ft_lstnew(f(lst->content));
	aux = new;
	lst = lst->next;
	while (lst != NULL)
	{
		temp = ft_lstnew(f(lst->content));
		if (temp == NULL)
		{
			ft_lstclear(&new, del);
			return (NULL);
		}
		aux->next = temp;
		aux = temp;
		lst = lst->next;
	}
	return (new);
}
