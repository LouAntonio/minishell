/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_delimiter.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 18:20:42 by hmateque          #+#    #+#             */
/*   Updated: 2024/12/14 18:20:43 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	check_quote_delimiter(t_node *head, char **delimiter)
{
	if (head->next->type == SING_QUOTE || head->next->type == DOUB_QUOTE)
	{
		if (head->next->type == SING_QUOTE)
			*delimiter = ft_strtrim(head->next->value, "'");
		else
			*delimiter = ft_strtrim(head->next->value, "\"");
		collect_mem(*delimiter);
	}
}

static char	*remove_quotes_wrapper(t_node **node, int *flag, int *has_quote)
{
	char	**strings;
	char	*new_str;

	if ((*node)->type == SING_QUOTE || (*node)->type == DOUB_QUOTE)
		*has_quote = 1;
	strings = remove_quotes((*node)->value, ' ');
	collect_words_mem(strings);
	new_str = strings[0];
	while ((*node) && (*node)->next && ((*node)->next_char != ' '
			&& (*node)->next_char != '\n' && (*node)->next_char != '\t')
		&& (*node)->next->type > HEREDOC)
	{
		*flag = 1;
		if ((*node)->next->type == SING_QUOTE
			|| (*node)->next->type == DOUB_QUOTE)
			*has_quote = 1;
		strings = remove_quotes((*node)->next->value, ' ');
		collect_words_mem(strings);
		new_str = ft_strjoin(new_str, strings[0]);
		collect_mem(new_str);
		(*node) = (*node)->next;
	}
	return (new_str);
}

void	join_delimiter(t_node *node)
{
	int		flag;
	int		has_quote;
	t_node	*tmp;
	char	*new_str;

	flag = 0;
	has_quote = 0;
	tmp = node;
	new_str = remove_quotes_wrapper(&node, &flag, &has_quote);
	if (flag == 1)
	{
		tmp->value = new_str;
		tmp->next_char = ' ';
		if (has_quote == 1)
			tmp->type = DOUB_QUOTE;
		tmp->next = node->next;
		if (node->next)
			node->next->prev = tmp;
	}
}
