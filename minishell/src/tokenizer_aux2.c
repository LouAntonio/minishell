/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_aux2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 22:17:52 by lantonio          #+#    #+#             */
/*   Updated: 2025/01/10 22:18:41 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*resize_word(char *word, int *capacity)
{
	char	*new_word;
	int		i;
	int		new_capacity;

	new_capacity = *capacity * 2;
	new_word = (char *)malloc(new_capacity * sizeof(char));
	if (new_word == NULL)
		return (NULL);
	collect_mem(new_word, MEM_CHAR_PTR, 0);
	i = 0;
	while (i < *capacity)
	{
		new_word[i] = word[i];
		i++;
	}
	*capacity = new_capacity;
	return (new_word);
}

int	handle_quote(t_word_data *data, char current_char)
{
	if (data->quote)
	{
		if (current_char == data->quote)
			return (finalize_quoted_word(data));
		else
			return (append_char_to_word(data, current_char));
	}
	return (0);
}

int	finalize_quoted_word(t_word_data *data)
{
	data->word[data->word_len++] = data->quote;
	data->word[data->word_len] = '\0';
	data->matrix[data->word_index++] = data->word;
	data->in_word = false;
	data->word = NULL;
	data->word_len = 0;
	data->word_capacity = 16;
	data->quote = '\0';
	return (1);
}

int	append_char_to_word(t_word_data *data, char current_char)
{
	if (data->word_len + 1 >= data->word_capacity)
	{
		data->word = resize_word(data->word, &data->word_capacity);
		if (data->word == NULL)
			return (-1);
	}
	data->word[data->word_len++] = current_char;
	return (1);
}

int	handle_quote_start(t_word_data *data, char current_char)
{
	if (current_char == '"' || current_char == '\'')
	{
		if (!data->in_word)
		{
			data->in_word = true;
			data->word = allocate_word(data->word_capacity);
			if (data->word == NULL)
				return (-1);
			collect_mem(data->word, MEM_CHAR_PTR, 0);
		}
		data->quote = current_char;
		data->word[data->word_len++] = current_char;
		return (1);
	}
	return (0);
}
