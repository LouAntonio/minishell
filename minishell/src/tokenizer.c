/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 09:39:33 by hmateque          #+#    #+#             */
/*   Updated: 2024/12/15 08:22:14 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	count_words(const char *input)
{
	int		count;
	bool	in_word;
	char	quote;

	count = 0;
	in_word = false;
	quote = '\0';
	for (int i = 0; input[i] != '\0'; i++)
	{
		if (quote)
		{
			if (input[i] == quote)
				quote = '\0';
		}
		else if (input[i] == '"' || input[i] == '\'')
		{
			if (!in_word)
				count++;
			quote = input[i];
			in_word = true;
		}
		else if (isspace(input[i]))
		{
			in_word = false;
		}
		else if (!in_word)
		{
			count++;
			in_word = true;
		}
	}
	return (count);
}

static char	*allocate_word(int capacity)
{
	return ((char *)malloc(capacity * sizeof(char)));
}

static char	*resize_word(char *word, int *capacity)
{
	int		i;
	int		new_capacity;
	char	*new_word;

	i = -1;
	new_capacity = *capacity * 2;
	new_word = (char *)malloc(new_capacity * sizeof(char));
	collect_mem(new_word);
	if (new_word == NULL)
		return (NULL);
	while (++i < *capacity)
		new_word[i] = word[i];
	*capacity = new_capacity;
	return (new_word);
}

static int	extract_words(const char *input, char **matrix, int *word_count)
{
	int		word_index;
	bool	in_word;
	char	*word;
	int		word_len;
	int		word_capacity;
	char	quote;

	word_index = 0;
	in_word = false;
	word = NULL;
	word_len = 0;
	word_capacity = 16;
	quote = '\0';
	for (int i = 0; input[i] != '\0'; i++)
	{
		if (quote)
		{
			if (input[i] == quote)
			{
				word[word_len++] = input[i];
				word[word_len] = '\0';
				matrix[word_index++] = word;
				in_word = false;
				word = NULL;
				word_len = 0;
				word_capacity = 16;
				quote = '\0';
			}
			else
			{
				if (word_len + 1 >= word_capacity)
				{
					word = resize_word(word, &word_capacity);
					if (word == NULL)
						return (-1);
				}
				word[word_len++] = input[i];
			}
		}
		else if (input[i] == '"' || input[i] == '\'')
		{
			if (!in_word)
			{
				in_word = true;
				word = allocate_word(word_capacity);
				collect_mem(word);
				if (word == NULL)
					return (-1);
			}
			quote = input[i];
			word[word_len++] = input[i];
		}
		else if (isspace(input[i]))
		{
			if (in_word)
			{
				word[word_len] = '\0';
				matrix[word_index++] = word;
				in_word = false;
				word = NULL;
				word_len = 0;
				word_capacity = 16;
			}
		}
		else
		{
			if (!in_word)
			{
				in_word = true;
				word = allocate_word(word_capacity);
				collect_mem(word);
				if (word == NULL)
					return (-1);
			}
			if (word_len + 1 >= word_capacity)
			{
				word = resize_word(word, &word_capacity);
				if (word == NULL)
					return (-1);
			}
			word[word_len++] = input[i];
		}
	}
	if (in_word)
	{
		word[word_len] = '\0';
		matrix[word_index++] = word;
	}
	matrix[word_index] = NULL;
	*word_count = word_index;
	return (word_index);
}

char	**ft_tokens(const char *input, int *word_count)
{
	char	**matrix;

	*word_count = count_words(input);
	matrix = (char **)malloc((*word_count + 1) * sizeof(char *));
	collect_mem(matrix);
	if (matrix == NULL)
	{
		free_all_mem();
		*word_count = 0;
		return (NULL);
	}
	if (extract_words(input, matrix, word_count) == -1)
	{
		free_all_mem();
		*word_count = 0;
		return (NULL);
	}
	return (matrix);
}
