/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 10:09:38 by lantonio          #+#    #+#             */
/*   Updated: 2025/01/11 10:09:39 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		count;
	t_list	*current;

	current = lst;
	count = 0;
	while (current != NULL)
	{
		current = current->next;
		count++;
	}
	return (count);
}
