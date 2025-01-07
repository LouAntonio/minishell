/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mudar_dps.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 11:13:21 by hmateque          #+#    #+#             */
/*   Updated: 2025/01/07 10:46:11 by hmateque         ###   ########.fr       */
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

Token	**classify_tokens(char **tokens, int word_count, t_env **env, int *g_returns)
{
	Token	**classified_tokens;
	char	*token;
	char	*stripped_token;
	size_t	len;
	int		i;

	(void)env;
	(void)g_returns;
	classified_tokens = malloc((word_count + 1) * sizeof(Token *));
	if (!classified_tokens)
		return (NULL);
	collect_mem(classified_tokens, MEM_CHAR_MATRIX, (word_count + 1));
	for (i = 0; i < word_count; i++)
	{
		classified_tokens[i] = malloc(sizeof(Token));
		if (!classified_tokens[i])
		{
			free_all_mem();
			return (NULL);
		}
		collect_mem(classified_tokens[i], MEM_TOKEN_PTR, 0);
		classified_tokens[i]->type = identify_token(tokens[i]);
		if (classified_tokens[i]->type == TOKEN_ARG && i > 0 &&
			classified_tokens[i - 1]->type == TOKEN_PIPE)
		{
			classified_tokens[i]->type = TOKEN_COMMAND;
		}
		else if (classified_tokens[i]->type == TOKEN_ARG && i == 0)
			classified_tokens[i]->type = TOKEN_COMMAND;
		token = tokens[i];
		len = ft_strlen(token);
		if ((token[0] == 39 && token[len - 1] == 39) || (token[0] == 34 && token[len - 1] == 34))
		{
			stripped_token = malloc((len - 1) * sizeof(char));
			if (!stripped_token)
			{
				free_all_mem();
				return (NULL);
			}
			collect_mem(stripped_token, MEM_CHAR_PTR, 0);
			strncpy(stripped_token, token + 1, len - 2);
			stripped_token[len - 2] = '\0';
			classified_tokens[i]->value = stripped_token;
		}
		else
			classified_tokens[i]->value = token;
	}
	return (classified_tokens[i] = NULL, classified_tokens);
}
