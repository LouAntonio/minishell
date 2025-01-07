/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 08:23:31 by hmateque          #+#    #+#             */
/*   Updated: 2025/01/07 14:20:11 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_env_list(t_env **env)
{
	t_env	*current;
	t_env	*next;

	if (!env || !*env)
		return ;
	current = *env;
	while (current)
	{
		next = current->next;
		free(current->name);
		free(current->value);
		free(current);
		current = next;
	}
	*env = NULL;
}

void	ft_exit(t_env **env, int status)
{
	free_env_list(env);
	if (status == 1)
		free_all_mem();
	ft_putstr_fd("exit\n", 1);
	exit(0);
}

void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	if (!matrix)
		return ;
	while (matrix[i] != NULL)
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

// void	free_all_mem(void)
// {
// 	t_list	**mem_list;
// 	t_list	*current;
// 	t_list	*next;

// 	mem_list = get_mem_address();
// 	current = *mem_list;
// 	while (current)
// 	{
// 		next = current->next;
// 		if (current->content)
// 		{
// 			void **matrix = (void **)current->content;
// 			size_t i = 0;
// 			if (matrix)
// 			{
// 				while (matrix[i])
// 				{
// 					free(matrix[i]);
// 					i++;
// 				}
// 			}
// 			free(matrix);
// 		}
// 		free(current);
// 		current = next;
// 	}
// 	*mem_list = NULL;
// }