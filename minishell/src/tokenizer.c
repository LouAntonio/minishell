/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 09:39:33 by hmateque          #+#    #+#             */
/*   Updated: 2025/01/10 22:29:10 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

#define MEM_CHAR_PTR 1
#define MEM_CHAR_PTR_PTR 2

void	initialize_extraction(t_word_data *data)
{
	data->word_index = 0;
	data->in_word = false;
	data->word = NULL;
	data->word_len = 0;
	data->word_capacity = 16;
	data->quote = '\0';
}

int	process_char(t_word_data *data, char current_char)
{
	int	result;

	result = handle_quote(data, current_char);
	if (result == -1)
		return (-1);
	if (result == 0)
	{
		result = handle_quote_start(data, current_char);
		if (result == -1)
			return (-1);
		if (result == 0)
		{
			if (isspace(current_char))
				handle_space(data);
			else if (handle_regular_char(data, current_char) == -1)
				return (-1);
		}
	}
	return (0);
}

int	extract_words(const char *input, t_word_data *data)
{
	int	i;

	initialize_extraction(data);
	i = 0;
	while (input[i] != '\0')
	{
		if (process_char(data, input[i]) == -1)
			return (-1);
		i++;
	}
	return (finalize_word(data));
}

char	**split_words(const char *input, int *word_count)
{
	t_word_data	data;
	int			count;

	count = count_words(input);
	data.matrix = (char **)malloc((count + 1) * sizeof(char *));
	if (data.matrix == NULL)
		return (NULL);
	collect_mem(data.matrix, MEM_CHAR_PTR_PTR, 0);
	*word_count = extract_words(input, &data);
	if (*word_count == -1)
		return (NULL);
	return (data.matrix);
}

char	**ft_tokens(const char *input, int *word_count)
{
	t_word_data	data;
	char		**matrix;

	*word_count = count_words(input);
	matrix = (char **)allocate_mem((*word_count + 1), sizeof(char *));
	if (matrix == NULL)
	{
		free_all_mem();
		*word_count = 0;
		return (NULL);
	}
	data.matrix = matrix;
	collect_mem(matrix, MEM_CHAR_MATRIX, (*word_count + 1));
	if (extract_words(input, &data) == -1)
	{
		free_all_mem();
		*word_count = 0;
		return (NULL);
	}
	return (matrix);
}
