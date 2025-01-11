/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_bin_tree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 11:48:26 by lantonio          #+#    #+#             */
/*   Updated: 2025/01/11 10:06:42 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	create_node(t_node *list, t_tree **root)
{
	*root = allocate_mem(1, sizeof(t_tree));
	(*root)->list = list;
	(*root)->right = NULL;
	(*root)->left = NULL;
}

void	build_tree(t_tree **root, t_node *list)
{
	t_node	**ptr_list;

	if (!list)
		return ;
	ptr_list = split_list(list);
	if (!ptr_list && list)
		return (create_node(list, root));
	if (ptr_list[1])
		create_node(ptr_list[1], root);
	if (ptr_list[0])
		build_tree(&(*root)->left, ptr_list[0]);
	if (ptr_list[2])
		build_tree(&(*root)->right, ptr_list[2]);
	else
		return ;
}
