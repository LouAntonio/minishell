/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 09:39:33 by hmateque          #+#    #+#             */
/*   Updated: 2024/11/18 12:42:20 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char **tokenize2(char *line) {
    int i, token_index, token_count;
    char **tokens;
    char *token;
    int in_quotes;
    char quote_char;
    
    tokens = malloc(MAX_TOKENS * sizeof(char *));
    if (!tokens) {
        perror("malloc error");
        exit(EXIT_FAILURE);
    }

    token = malloc(MAX_TOKEN_LENGTH * sizeof(char));
    if (!token) {
        perror("malloc error");
        exit(EXIT_FAILURE);
    }

    token_count = 0;
    token_index = 0;
    in_quotes = 0;
    quote_char = '\0';
    i = 0;

    while (line[i]) {
        if (!in_quotes && (line[i] == '\'' || line[i] == '"')) {
            in_quotes = 1;
            quote_char = line[i];
        } else if (in_quotes && line[i] == quote_char) {
            in_quotes = 0;
            quote_char = '\0';
        } else if (!in_quotes && (isspace(line[i]) || line[i] == '|' || line[i] == '<' || line[i] == '>')) {
            if (token_index > 0) {
                token[token_index] = '\0';
                tokens[token_count++] = strdup(token);
                token_index = 0;
            }
            if (line[i] == '>' && line[i + 1] == '>') {
                tokens[token_count++] = strdup(">>");
                i++;
            } else if (line[i] == '<' && line[i + 1] == '<') {
                tokens[token_count++] = strdup("<<");
                i++;
            } else if (line[i] == '|' || line[i] == '<' || line[i] == '>') {
                char operator[2] = { line[i], '\0' };
                tokens[token_count++] = strdup(operator);
            }
        } else {
            token[token_index++] = line[i];
        }
        i++;
    }

    if (token_index > 0) {
        token[token_index] = '\0';
        tokens[token_count++] = strdup(token);
    }

    tokens[token_count] = NULL;
    free(token);
    return tokens;
}

char	**tokenize(char *line)
{
	int		i;
	char	**tokens;
	char	*token;
	int		token_count;
	int		token_index;
	int		in_quotes;
	char	quote_char;

	tokens = malloc(MAX_TOKENS * sizeof(char *));
	token = malloc(MAX_TOKEN_LENGTH * sizeof(char));
	token_count = 0;
	token_index = 0;
	in_quotes = 0;
	quote_char = '\0';
	i = -1;
	while (line[++i])
	{
		if (!in_quotes && (line[i] == '\'' || line[i] == '"'))
		{
			in_quotes = 1;
			quote_char = line[i];
		}
		else if (in_quotes && line[i] == quote_char)
		{
			in_quotes = 0;
			quote_char = '\0';
		}
		else if (!in_quotes && (isspace(line[i]) || line[i] == '|'
				|| line[i] == '<' || line[i] == '>'))
		{
			if (token_index > 0)
			{
				token[token_index] = '\0';
				tokens[token_count] = strdup(token);
				token_count++;
				token_index = 0;
			}
			if (!isspace(line[i]))
			{
				if (line[i] == '>' && line[i + 1] == '>')
				{
					token[0] = '>';
					token[1] = '>';
					token[2] = '\0';
					tokens[token_count] = strdup(token);
					token_count++;
					i++;
				}
				else if (line[i] == '<' && line[i + 1] == '<')
				{
					token[0] = '<';
					token[1] = '<';
					token[2] = '\0';
					tokens[token_count] = strdup(token);
					token_count++;
					i++;
				}
				else
				{
					token[0] = line[i];
					token[1] = '\0';
					tokens[token_count] = strdup(token);
					token_count++;
				}
			}
		}
		else
			token[token_index++] = line[i];
	}
	if (token_index > 0)
	{
		token[token_index] = '\0';
		tokens[token_count] = strdup(token);
		token_count++;
	}
	tokens[token_count] = NULL;
	free(token);
	return (tokens);
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

Token	**classify_tokens(char **tokens)
{
	int		i;
	Token	**classified_tokens;
	Token	*t;

	i = 0;
	classified_tokens = malloc(64 * sizeof(Token *));
	if (tokens[i] != NULL)
	{
		t = malloc(sizeof(Token));
		t->value = tokens[i];
		t->type = TOKEN_COMMAND;
		classified_tokens[i] = t;
	}
	while (tokens[++i] != NULL)
	{
		t = malloc(sizeof(Token));
		t->value = tokens[i];
		if (i > 0 && classified_tokens[i - 1]->type == TOKEN_PIPE)
			t->type = TOKEN_COMMAND;
		else
			t->type = identify_token(tokens[i]);
		classified_tokens[i] = t;
	}
	classified_tokens[i] = NULL;
	return (classified_tokens);
}

Command	*build_command_tree(Token **tokens)
{
	int		i;
	int		arg_index;
	Command	*root;
	Command	*current;
	Command	*new_cmd;

	i = 0;
	root = NULL;
	current = NULL;
	while (tokens[i] != NULL)
	{
		if (tokens[i]->type == TOKEN_COMMAND)
		{
			new_cmd = malloc(sizeof(Command));
			new_cmd->command = tokens[i]->value;
			new_cmd->args = malloc(64 * sizeof(char *));
			new_cmd->redirect_out = NULL;
			new_cmd->redirect_in = NULL;
			new_cmd->next = NULL;
			new_cmd->heredoc = 0;
			new_cmd->heredoc_end = NULL;
			arg_index = 0;
			while (tokens[i + 1] != NULL && tokens[i + 1]->type == TOKEN_ARG)
			{
				if (arg_index == 0)
					new_cmd->args[arg_index++] = "";
				else
					new_cmd->args[arg_index++] = tokens[++i]->value;
			}
			new_cmd->args[arg_index] = NULL;
			if (root == NULL)
			{
				root = new_cmd;
				current = root;
			}
			else
			{
				current->next = new_cmd;
				current = current->next;
			}
		}
		else if (tokens[i]->type == TOKEN_REDIRECT_OUT)
		{
			current->redirect_out_type = 1;
			if (current != NULL)
			{
				if (tokens[i + 1])
					current->redirect_out = tokens[++i]->value;
				else
					return (printf("minishell: syntax error near unexpected token `newline'\n"), NULL);
			}
		}
		else if (tokens[i]->type == TOKEN_APPEND_OUT)
		{
			current->redirect_out_type = 2;
			if (current != NULL)
			{
				if (tokens[i + 1])
					current->redirect_out = tokens[++i]->value;
				else
					return (printf("minishell: syntax error near unexpected token `newline'\n"), NULL);
			}
		}
		else if (tokens[i]->type == TOKEN_REDIRECT_IN)
		{
			if (current != NULL)
			{
				if (tokens[i + 1])
					current->redirect_in = tokens[++i]->value;
				else
					return (printf("minishell: syntax error near unexpected token `newline'\n"), NULL);
			}
		}
		else if (tokens[i]->type == TOKEN_HEREDOC)
		{
			if (current != NULL)
			{
				if (tokens[i + 1])
				{
					current->heredoc = 1;
					current->heredoc_end = tokens[++i]->value;
				}
				else
					return (printf("minishell: syntax error near unexpected token `newline'\n"), NULL);
			}
		}
		i++;
	}
	return (root);
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
