/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mudar_dps.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 11:13:21 by hmateque          #+#    #+#             */
/*   Updated: 2024/12/12 12:18:34 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	(void)env;
	(void)g_returns;
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
			classified_tokens[i]->value = stripped_token;
		}
		else if (token[0] == 34 || token[0] == 39 || token[len - 1] == 34 || token[len - 1] == 39)
		{
			if (token[0] != token[len - 1])
				return (printf("Error\n"), NULL);
		}
		else
			classified_tokens[i]->value = token;
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