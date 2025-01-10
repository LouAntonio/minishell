/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 22:18:23 by lantonio          #+#    #+#             */
/*   Updated: 2025/01/10 22:37:01 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	**classify_tokens(char **tokens, int wc, t_env **env, int *g_returns)
{
	t_token	**classified_tokens;

	(void)env;
	(void)g_returns;
	classified_tokens = allocate_classified_tokens(wc);
	if (!classified_tokens)
		return (NULL);
	classify_token_type(classified_tokens, tokens, wc);
	classified_tokens[wc] = NULL;
	return (classified_tokens);
}

int	handle_space(t_word_data *data)
{
	if (data->in_word)
	{
		data->word[data->word_len] = '\0';
		data->matrix[data->word_index++] = data->word;
		data->in_word = false;
		data->word = NULL;
		data->word_len = 0;
		data->word_capacity = 16;
	}
	return (0);
}

int	handle_regular_char(t_word_data *data, char current_char)
{
	if (!data->in_word)
	{
		data->in_word = true;
		data->word = allocate_word(data->word_capacity);
		if (data->word == NULL)
			return (-1);
		collect_mem(data->word, MEM_CHAR_PTR, 0);
	}
	return (append_char_to_word(data, current_char));
}

int	finalize_word(t_word_data *data)
{
	if (data->in_word)
	{
		data->word[data->word_len] = '\0';
		data->matrix[data->word_index++] = data->word;
	}
	data->matrix[data->word_index] = NULL;
	return (data->word_index);
}
