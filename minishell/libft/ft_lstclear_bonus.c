/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 10:08:58 by lantonio          #+#    #+#             */
/*   Updated: 2025/01/11 10:08:59 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*current;
	t_list	*aux;

	if (lst == NULL || del == NULL)
		return ;
	current = *lst;
	while (current != NULL)
	{
		aux = current->next;
		del(current->content);
		free(current);
		current = aux;
	}
	*lst = NULL;
}
