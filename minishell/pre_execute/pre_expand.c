/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 18:22:07 by hmateque          #+#    #+#             */
/*   Updated: 2024/12/14 18:22:07 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	collect_words_mem(char **words)
{
	int	i;

	i = 0;
	while (words[i])
	{
		collect_mem(words[i]);
		i++;
	}
	collect_mem(words);
}

static void	count_quotes(char *str, int *sing_quote, int *double_quote)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			*sing_quote = *sing_quote + 1;
		else if (str[i] == '"')
			*double_quote = *double_quote + 1;
		i++;
	}
}

static char	*repair_quotes(char *str)
{
	int		sing_quote;
	int		double_quote;
	char	*tmp;

	sing_quote = 0;
	double_quote = 0;
	count_quotes(str, &sing_quote, &double_quote);
	if (sing_quote % 2 != 0)
	{
		tmp = ft_strjoin("\"", str);
		str = ft_strjoin(tmp, "\"");
		collect_mem(str);
		free(tmp);
	}
	else if (double_quote % 2 != 0)
	{
		tmp = ft_strjoin("\'", str);
		str = ft_strjoin(tmp, "\'");
		collect_mem(str);
		free(tmp);
	}
	return (str);
}

void	preprocess_expansion(t_node *node)
{
	while (node)
	{
		if (node->type != SING_QUOTE)
			node->value = expand(node);
		if (node->type == EXPAND && node->value)
			node->value = repair_quotes(node->value);
		node = node->next;
	}
}
