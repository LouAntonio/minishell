/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_file2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 12:17:57 by hmateque          #+#    #+#             */
/*   Updated: 2025/01/10 12:27:45 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

t_list	**get_mem_address(void)
{
	static t_list	*ptr;

	return (&ptr);
}

void	collect_mem(void *ptr, t_mem_type type, size_t size)
{
	t_memory	*mem;

	if (!ptr)
		return ;
	mem = malloc(sizeof(t_memory));
	if (!mem)
		exit(ENOMEM);
	mem->ptr = ptr;
	mem->type = type;
	mem->size = size;
	ft_lstadd_back(get_mem_address(), ft_lstnew(mem));
}

void	*allocate_mem(size_t nmemb, size_t size)
{
	void	*content;

	content = ft_calloc(nmemb, size);
	if (content == NULL)
		exit(ENOMEM);
	return (content);
}

static void	free_memory_content(void *ptr)
{
	t_memory	*mem;

	if (!ptr)
		return ;
	mem = (t_memory *)ptr;
	if (mem->ptr)
	{
		free(mem->ptr);
		mem->ptr = NULL;
	}
	free(mem);
}

static void	free_list_node(t_list *node)
{
	if (!node)
		return ;
	if (node->content)
		free_memory_content(node->content);
	free(node);
}

void	free_all_mem(void)
{
	t_list		**mem_list;
	t_list		*current;
	t_list		*next;

	mem_list = get_mem_address();
	if (!mem_list || !*mem_list)
		return ;
	current = *mem_list;
	while (current)
	{
		next = current->next;
		free_list_node(current);
		current = next;
	}
	*mem_list = NULL;
}
