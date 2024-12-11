/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 09:39:33 by hmateque          #+#    #+#             */
/*   Updated: 2024/12/10 08:04:00 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**ft_tokens(const char *input, int *word_count)
{
	int		count;
	int		in_word;
	int		in_quotes;
	char	quote_char;

	count = 0;
	in_word = 0;
	in_quotes = 0;
	quote_char = '\0';
	// Contagem de palavras
	for (int i = 0; input[i] != '\0'; i++)
	{
		if (input[i] == 34 || input[i] == 39)
		{
			if (!in_quotes)
			{
				in_quotes = 1;
				quote_char = input[i];
				count++;
			}
			else if (input[i] == quote_char)
			{
				in_quotes = 0;
				quote_char = '\0';
			}
		}
		else if (isspace(input[i]) && !in_quotes)
		{
			in_word = 0;
		}
		else if (!in_word)
		{
			count++;
			in_word = 1;
		}
	}
	char **matrix = (char **)malloc(count * sizeof(char *));
	if (matrix == NULL)
		return (*word_count = 0, NULL);
	int word_index = 0;
	in_word = 0;
	in_quotes = 0;
	quote_char = '\0';
	char *word = NULL;
	int word_len = 0;
	int word_capacity = 0;
	// Extração de palavras
	for (int i = 0; input[i] != '\0'; i++)
	{
		if (input[i] == 34 || input[i] == 39)
		{
			if (!in_quotes)
			{
				in_quotes = 1;
				quote_char = input[i];
				in_word = 1;
				word_len = 0;
				word_capacity = 16;
				word = (char *)malloc(word_capacity * sizeof(char));
				if (word == NULL)
				{
					for (int j = 0; j < word_index; j++)
						free(matrix[j]);
					free(matrix);
					*word_count = 0;
					return (NULL);
				}
				word[word_len++] = input[i]; // Adiciona a aspas de abertura
			}
			else if (input[i] == quote_char)
			{
				word[word_len++] = input[i]; // Adiciona a aspas de fechamento
				word[word_len] = '\0';
				matrix[word_index++] = word;
				in_quotes = 0;
				quote_char = '\0';
				word = NULL;
				word_len = 0;
				word_capacity = 0;
				in_word = 0;
			}
		}
		else if (isspace(input[i]) && !in_quotes)
		{
			if (in_word)
			{
				word[word_len] = '\0';
				matrix[word_index++] = word;
				in_word = 0;
				word = NULL;
				word_len = 0;
				word_capacity = 0;
			}
		}
		else
		{
			if (!in_word)
			{
				in_word = 1;
				word_len = 0;
				word_capacity = 16;
				word = (char *)malloc(word_capacity * sizeof(char));
				if (word == NULL)
				{
					for (int j = 0; j < word_index; j++)
						free(matrix[j]);
					free(matrix);
					*word_count = 0;
					return (NULL);
				}
			}
			if (word_len + 1 >= word_capacity)
			{
				word_capacity *= 2;
				char *new_word = (char *)realloc(word, word_capacity * sizeof(char));
				if (new_word == NULL)
				{
					free(word);
					for (int j = 0; j < word_index; j++)
						free(matrix[j]);
					free(matrix);
					*word_count = 0;
					return (NULL);
				}
				word = new_word;
			}
			word[word_len++] = input[i];
		}
	}
	if (in_word)
	{
		word[word_len] = '\0';
		matrix[word_index++] = word;
	}
	*word_count = word_index;
	return (matrix);
}

void free_matrix_tokens(char** matrix, int word_count) 
{
	for (int i = 0; i < word_count; i++) {
		free(matrix[i]);
	}
	free(matrix);
}

TokenType	identify_token(char *token)
{
	if (ft_strncmp(token, "|", 1) == 0)
		return (TOKEN_PIPE);
	else if (ft_strncmp(token, ">>", 2) == 0)
		return (TOKEN_APPEND_OUT);
	else if (ft_strncmp(token, ">", 1) == 0)
		return (TOKEN_REDIRECT_OUT);
	else if (ft_strncmp(token, "<<", 2) == 0)
		return (TOKEN_HEREDOC);
	else if (ft_strncmp(token, "<", 1) == 0)
		return (TOKEN_REDIRECT_IN);
	return (TOKEN_ARG);
}

Token **classify_tokens(char **tokens, int word_count, t_env **env, int *g_returns)
{
	Token   **classified_tokens;
	char    *token;
	char    *stripped_token;
	size_t  len;
	int     i;

	classified_tokens = malloc((word_count + 1) * sizeof(Token *));
	if (!classified_tokens)
		return NULL;
	for (i = 0; i < word_count; i++)
	{
		classified_tokens[i] = malloc(sizeof(Token));
		if (!classified_tokens[i])
		{
			for (int j = 0; j < i; j++)
				free(classified_tokens[j]);
			free(classified_tokens);
			return NULL;
		}
		classified_tokens[i]->type = identify_token(tokens[i]);
		if (classified_tokens[i]->type == TOKEN_ARG && i > 0 && 
			classified_tokens[i - 1]->type == TOKEN_PIPE)
		{
			classified_tokens[i]->type = TOKEN_COMMAND;
		}
		else if (classified_tokens[i]->type == TOKEN_ARG && i == 0)
			classified_tokens[i]->type = TOKEN_COMMAND;
		token = tokens[i];
		len = strlen(token);
		if (token[0] == 39 && token[len - 1] == 39)
		{
			if (len == 1)
				return (printf("Error\n"), NULL);
			stripped_token = malloc((len - 1) * sizeof(char));
			if (!stripped_token)
			{
				for (int j = 0; j <= i; j++)
					free(classified_tokens[j]);
				free(classified_tokens);
				return NULL;
			}
			strncpy(stripped_token, token + 1, len - 2);
			stripped_token[len - 2] = '\0';
			classified_tokens[i]->value = stripped_token;
		}
		else if (token[0] == 34 && token[len - 1] == 34)
		{
			if (len == 1)
				return (printf("Error\n"), NULL);
			char *stripped_token = malloc((len - 1) * sizeof(char));
			if (!stripped_token)
			{
				for (int j = 0; j <= i; j++)
					free(classified_tokens[j]);
				free(classified_tokens);
				return NULL;
			}
			strncpy(stripped_token, token + 1, len - 2);
			stripped_token[len - 2] = '\0';
			stripped_token = expand_variable(stripped_token, *env, g_returns);
			classified_tokens[i]->value = stripped_token;
		}
		else if (token[0] == 34 || token[0] == 39 || token[len - 1] == 34 || token[len - 1] == 39)
		{
			if (token[0] != token[len - 1])
				return (printf("Error\n"), NULL);
		}
		else
			classified_tokens[i]->value = expand_variable(token, *env, g_returns);
	}
	return (classified_tokens[i] = NULL, classified_tokens);
}

int	validate_command_tree(Command *root)
{
	Command	*current;

	current = root;
	while (current != NULL)
	{
		if (current->redirect_out != NULL)
		{
			if (access(current->redirect_out, F_OK) == -1)
			{
				printf("Erro: Arquivo %s não encontrado para saída\n",
					current->redirect_out);
				return (0);
			}
		}
		if (current->redirect_in != NULL)
		{
			if (access(current->redirect_in, R_OK) == -1)
			{
				printf("Erro: Arquivo %s não encontrado para entrada\n",
					current->redirect_in);
				return (0);
			}
		}
		if (current->command == NULL || current->args == NULL)
			return (printf("Erro: Comando inválido\n"), 0);
		current = current->next;
	}
	return (1);
}
