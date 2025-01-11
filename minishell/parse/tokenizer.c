/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 12:30:39 by cogata            #+#    #+#             */
/*   Updated: 2024/12/10 08:57:20 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_node	*tokenizer(char *input)
{
	t_node	*head;
	t_node	*node;

	head = NULL;
	while (*input != '\0')
	{
		node = split_token(&input);
		if (node == NULL)
			break ;
		add_token(&head, node);
	}
	return (head);
}

t_node	*split_token(char **input)
{
	int		i;
	char	*temp;
	t_node	*node;

	i = 0;
	temp = *input;
	node = NULL;
	while (temp[i] == ' ' || temp[i] == '\n' || temp[i] == '\t')
	{
		i++;
		*input = *input + 1;
	}
	lookfor_token(&node, input, temp, i);
	return (node);
}

void	add_token(t_node **head, t_node *node)
{
	t_node	*temp;

	temp = *head;
	if (*head == NULL)
	{
		*head = node;
		node->prev = NULL;
		node->next = NULL;
	}
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = node;
		node->prev = temp;
	}
}
