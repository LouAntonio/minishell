/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 00:04:17 by hmateque          #+#    #+#             */
/*   Updated: 2025/01/06 11:43:19 by hmateque         ###   ########.fr       */
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

	mem_list = get_mem_address();
	current = *mem_list;
	while (current)
	{
		next = current->next;
		if (current->content)
		{
			void **matrix = (void **)current->content;
			size_t i = 0;
			if (matrix)
			{
				while (matrix[i])
				{
					free(matrix[i]);
					i++;
				}
				printf("i = %ld\n", i);
			}
			free(matrix);
		}
		free(current);
		current = next;
	}
	*mem_list = NULL;
}

