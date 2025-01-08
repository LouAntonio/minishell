/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_file2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 12:17:57 by hmateque          #+#    #+#             */
/*   Updated: 2025/01/07 16:10:31 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

// Função auxiliar para liberar matriz de strings
// static void free_str_matrix(char **matrix)
// {
//     size_t i;

//     if (!matrix)
//         return;
//     i = 0;
//     while (matrix[i])
//     {
//         free(matrix[i]);
//         i++;
//     }
//     free(matrix);
// }

t_list	**get_mem_address(void)
{
	static t_list	*ptr;

	return (&ptr);
}

// Função para coletar memória alocada
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

// Função para liberar toda a memória
void	free_all_mem(void)
{
	t_list		**mem_list;
	t_list		*current;
	t_list		*next;
	t_memory	*mem;

	mem_list = get_mem_address();
	if (!mem_list || !*mem_list)
		return ;
	current = *mem_list;
	while (current)
	{
		next = current->next;
		if (current->content)
		{
			mem = (t_memory *)current->content;
			if (mem->ptr)
			{
				switch (mem->type)
				{
					case MEM_CHAR_PTR:
						if (mem->ptr)
						{
							free(mem->ptr);
							mem->ptr = NULL;
						}
					break ;
					case MEM_CHAR_MATRIX:
						if (mem->ptr)
						{
							free(mem->ptr);
							mem->ptr = NULL;
						}
					break ;
					case MEM_TOKEN_PTR:
						if (mem->ptr)
						{
							free(mem->ptr);
							mem->ptr = NULL;
						}
					break ;
					case MEM_COMMAND:
						if (mem->ptr)
						{
							free(mem->ptr);
							mem->ptr = NULL;
						}
					break ;
					default:
						if (mem->ptr)
						{
							free(mem->ptr);
							mem->ptr = NULL;
						}
					break ;
				}
			}
			free(mem);
		}
		free(current);
		current = next;
	}
	*mem_list = NULL;
}
