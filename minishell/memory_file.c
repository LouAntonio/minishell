/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 00:04:17 by hmateque          #+#    #+#             */
/*   Updated: 2025/01/07 16:06:55 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

t_list	**get_mem_address(void)
{
	static t_list	*ptr;

	return (&ptr);
}

void	collect_mem(void *content)
{
	ft_lstadd_back(get_mem_address(), ft_lstnew(content));
}

void	*allocate_mem(size_t nmemb, size_t size)
{
	void	*content;

	content = ft_calloc(nmemb, size);
	if (content == NULL)
		exit(ENOMEM);
	collect_mem(content);
	return (content);
}

void	free_all_mem(void)
{
	t_list	**mem_list;
	t_list	*current;
	t_list	*next;
	void	**matrix;
	size_t	i;

	mem_list = get_mem_address();
	current = *mem_list;
	while (current)
	{
		next = current->next;
		if (current->content)
		{
			matrix = (void **)current->content;
			i = -1;
			if (matrix)
				while (matrix[++i])
					free(matrix[i]);
			free(matrix);
		}
		free(current);
		current = next;
	}
	*mem_list = NULL;
}
