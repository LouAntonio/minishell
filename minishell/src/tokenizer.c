/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 09:39:33 by hmateque          #+#    #+#             */
/*   Updated: 2025/01/10 09:11:38 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	count_words(const char *input)
{
	int		count;
	bool	in_word;
	char	quote;
	int		i;

	count = 0;
	in_word = false;
	quote = '\0';
	i = 0;
	while (input[i] != '\0')
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
		i++;
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
	if (new_word == NULL)
		return (NULL);
	collect_mem(new_word, MEM_CHAR_PTR, 0);
	while (++i < *capacity)
		new_word[i] = word[i];
	*capacity = new_capacity;
	return (new_word);
}

// static int	extract_words(const char *input, char **matrix, int *word_count)
// {
// 	int		word_index;
// 	bool	in_word;
// 	char	*word;
// 	int		word_len;
// 	int		word_capacity;
// 	char	quote;
// 	int		i;

// 	i = 0;
// 	word_index = 0;
// 	in_word = false;
// 	word = NULL;
// 	word_len = 0;
// 	word_capacity = 16;
// 	quote = '\0';
// 	while (input[i] != '\0')
// 	{
// 		if (quote)
// 		{
// 			if (input[i] == quote)
// 			{
// 				word[word_len++] = input[i];
// 				word[word_len] = '\0';
// 				matrix[word_index++] = word;
// 				in_word = false;
// 				word = NULL;
// 				word_len = 0;
// 				word_capacity = 16;
// 				quote = '\0';
// 			}
// 			else
// 			{
// 				if (word_len + 1 >= word_capacity)
// 				{
// 					word = resize_word(word, &word_capacity);
// 					if (word == NULL)
// 						return (-1);
// 				}
// 				word[word_len++] = input[i];
// 			}
// 		}
// 		else if (input[i] == '"' || input[i] == '\'')
// 		{
// 			if (!in_word)
// 			{
// 				in_word = true;
// 				word = allocate_word(word_capacity);
// 				if (word == NULL)
// 					return (-1);
// 				collect_mem(word, MEM_CHAR_PTR, 0);
// 			}
// 			quote = input[i];
// 			word[word_len++] = input[i];
// 		}
// 		else if (isspace(input[i]))
// 		{
// 			if (in_word)
// 			{
// 				word[word_len] = '\0';
// 				matrix[word_index++] = word;
// 				in_word = false;
// 				word = NULL;
// 				word_len = 0;
// 				word_capacity = 16;
// 			}
// 		}
// 		else
// 		{
// 			if (!in_word)
// 			{
// 				in_word = true;
// 				word = allocate_word(word_capacity);
// 				if (word == NULL)
// 					return (-1);
// 				collect_mem(word, MEM_CHAR_PTR, 0);
// 			}
// 			if (word_len + 1 >= word_capacity)
// 			{
// 				word = resize_word(word, &word_capacity);
// 				if (word == NULL)
// 					return (-1);
// 			}
// 			word[word_len++] = input[i];
// 		}
// 		i++;
// 	}
// 	if (in_word)
// 	{
// 		word[word_len] = '\0';
// 		matrix[word_index++] = word;
// 	}
// 	matrix[word_index] = NULL;
// 	*word_count = word_index;
// 	return (word_index);
// }

static int	handle_quote(char **word, int *word_len, int *word_capacity, 
						char *quote, char current_char, int *word_index, 
						char **matrix, bool *in_word)
{
	if (*quote)
	{
		if (current_char == *quote)
		{
			(*word)[(*word_len)++] = current_char;
			(*word)[*word_len] = '\0';
			matrix[(*word_index)++] = *word;
			*in_word = false;
			*word = NULL;
			*word_len = 0;
			*word_capacity = 16;
			*quote = '\0';
		}
		else
		{
			if (*word_len + 1 >= *word_capacity)
			{
				*word = resize_word(*word, word_capacity);
				if (*word == NULL)
					return (-1);
			}
			(*word)[(*word_len)++] = current_char;
		}
		return (1);
	}
	return (0);
}

static int	handle_quote_start(char **word, int *word_len, int word_capacity,
							char *quote, char current_char, bool *in_word)
{
	if (current_char == '"' || current_char == '\'')
	{
		if (!*in_word)
		{
			*in_word = true;
			*word = allocate_word(word_capacity);
			if (*word == NULL)
				return (-1);
			collect_mem(*word, MEM_CHAR_PTR, 0);
		}
		*quote = current_char;
		(*word)[(*word_len)++] = current_char;
		return (1);
	}
	return (0);
}

static int	handle_space(char **word, int *word_len, int *word_capacity,
						bool *in_word, int *word_index, char **matrix)
{
	if (*in_word)
	{
		(*word)[*word_len] = '\0';
		matrix[(*word_index)++] = *word;
		*in_word = false;
		*word = NULL;
		*word_len = 0;
		*word_capacity = 16;
	}
	return (0);
}

static int	handle_regular_char(char **word, int *word_len, int *word_capacity,
							bool *in_word, char current_char)
{
	if (!*in_word)
	{
		*in_word = true;
		*word = allocate_word(*word_capacity);
		if (*word == NULL)
			return (-1);
		collect_mem(*word, MEM_CHAR_PTR, 0);
	}
	if (*word_len + 1 >= *word_capacity)
	{
		*word = resize_word(*word, word_capacity);
		if (*word == NULL)
			return (-1);
	}
	(*word)[(*word_len)++] = current_char;
	return (0);
}

static int	finalize_word(char **word, int *word_len, bool *in_word,
						int *word_index, char **matrix)
{
	if (*in_word)
	{
		(*word)[*word_len] = '\0';
		matrix[(*word_index)++] = *word;
	}
	matrix[*word_index] = NULL;
	return (*word_index);
}

static int	extract_words(const char *input, char **matrix, int *word_count)
{
	int		word_index;
	bool	in_word;
	char	*word;
	int		word_len;
	int		word_capacity;
	char	quote;
	int		i;
	int		result;

	i = 0;
	word_index = 0;
	in_word = false;
	word = NULL;
	word_len = 0;
	word_capacity = 16;
	quote = '\0';
	while (input[i] != '\0')
	{
		result = handle_quote(&word, &word_len, &word_capacity, &quote,
				input[i], &word_index, matrix, &in_word);
		if (result == -1)
			return (-1);
		if (result == 0)
		{
			result = handle_quote_start(&word, &word_len, word_capacity,
					&quote, input[i], &in_word);
			if (result == -1)
				return (-1);
			if (result == 0)
			{
				if (isspace(input[i]))
					handle_space(&word, &word_len, &word_capacity,
						&in_word, &word_index, matrix);
				else if (handle_regular_char(&word, &word_len, &word_capacity,
						&in_word, input[i]) == -1)
					return (-1);
			}
		}
		i++;
	}
	*word_count = finalize_word(&word, &word_len, &in_word, &word_index, matrix);
	return (word_index);
}

char	**ft_tokens(const char *input, int *word_count)
{
	char	**matrix;

	*word_count = count_words(input);
	matrix = (char **)allocate_mem((*word_count + 1), sizeof(char *));
	if (matrix == NULL)
	{
		free_all_mem();
		*word_count = 0;
		return (NULL);
	}
	collect_mem(matrix, MEM_CHAR_MATRIX, (*word_count + 1));
	if (extract_words(input, matrix, word_count) == -1)
	{
		free_all_mem();
		*word_count = 0;
		return (NULL);
	}
	return (matrix);
}
