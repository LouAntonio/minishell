/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 18:21:32 by hmateque          #+#    #+#             */
/*   Updated: 2024/12/14 18:21:33 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	init_node(t_node **node, char *str)
{
	*node = allocate_mem(1, sizeof(t_node));
	(*node)->value = ft_strdup(str);
	collect_mem((*node)->value);
	(*node)->next = NULL;
}

t_node	*create_meta_node(char **input, char *str, int move)
{
	t_node	*node;

	node = NULL;
	init_node(&node, str);
	if (!ft_strncmp(str, "&&", 2))
		node->type = AND;
	else if (!ft_strncmp(str, "||", 2))
		node->type = OR;
	else if (!ft_strncmp(str, "|", 1))
		node->type = PIPE;
	else if (!ft_strncmp(str, ">>", 2))
		node->type = APPEND;
	else if (!ft_strncmp(str, "<<", 2))
		node->type = HEREDOC;
	else if (!ft_strncmp(str, "<", 1))
		node->type = IN_REDIR;
	else if (!ft_strncmp(str, ">", 1))
		node->type = OUT_REDIR;
	else if (!ft_strncmp(str, "(", 1))
		node->type = OPEN_PAR;
	else if (!ft_strncmp(str, ")", 1))
		node->type = CLOSE_PAR;
	*input = *input + move;
	node->next_char = input[0][0];
	return (node);
}

t_node	*create_word_node(char *value, int type, char next_char)
{
	t_node	*node;

	node = allocate_mem(1, sizeof(t_node));
	if (node == NULL)
		return (NULL);
	node->value = value;
	node->type = type;
	node->next_char = next_char;
	node->next = NULL;
	return (node);
}
