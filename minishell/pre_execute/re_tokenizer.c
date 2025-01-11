/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_tokenizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 18:22:12 by hmateque          #+#    #+#             */
/*   Updated: 2024/12/14 18:22:13 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_node	*retokenizer(char **words)
{
	int		i;
	t_node	*new_list;

	i = 0;
	new_list = NULL;
	while (words[i])
	{
		add_token(&new_list, create_word_node(words[i], WORD, ' '));
		i++;
	}
	return (new_list);
}

char	*rejoin(t_tree *root)
{
	char	*str;
	t_node	*list;

	str = NULL;
	list = root->list;
	while (list)
	{
		if (list->value && !str)
		{
			str = ft_strdup(list->value);
			collect_mem(str);
		}
		else if (list->value && str)
		{
			str = ft_strjoin(str, list->value);
			collect_mem(str);
		}
		if (list->next_char == ' ' || list->next_char == '\n'
			|| list->next_char == '\t')
			str = add_char_to_str(str, ' ');
		list = list->next;
	}
	return (str);
}
