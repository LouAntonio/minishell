/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 10:07:00 by lantonio          #+#    #+#             */
/*   Updated: 2025/01/11 10:07:03 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_mem(t_list **list)
{
	t_list	*cur;

	while (*list)
	{
		cur = (*list)->next;
		if ((*list)->content)
		{
			free((*list)->content);
			(*list)->content = NULL;
		}
		free(*list);
		*list = NULL;
		*list = cur;
	}
}
