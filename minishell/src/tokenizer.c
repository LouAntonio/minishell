/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 09:39:33 by hmateque          #+#    #+#             */
/*   Updated: 2024/11/06 16:27:21 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char **tokenize(char *line)
{
    char **tokens = malloc(MAX_TOKENS * sizeof(char *));
    char *token = malloc(MAX_TOKEN_LENGTH * sizeof(char));
    int token_count = 0;
    int token_index = 0;
    int in_quotes = 0;
    char quote_char = '\0';

    for (int i = 0; line[i] != '\0'; i++) {
        if (!in_quotes && (line[i] == '\'' || line[i] == '"')) {
            in_quotes = 1;
            quote_char = line[i];
        } else if (in_quotes && line[i] == quote_char) {
            in_quotes = 0;
            quote_char = '\0';
        } else if (!in_quotes && (isspace(line[i]) || line[i] == '|' || line[i] == '<' || line[i] == '>')) {
            if (token_index > 0) {
                token[token_index] = '\0';
                tokens[token_count] = strdup(token);
                token_count++;
                token_index = 0;
            }
            if (!isspace(line[i])) {
                token[0] = line[i];
                token[1] = '\0';
                tokens[token_count] = strdup(token);
                token_count++;
            }
        } else {
            token[token_index++] = line[i];
        }
    }

    if (token_index > 0) {
        token[token_index] = '\0';
        tokens[token_count] = strdup(token);
        token_count++;
    }

    tokens[token_count] = NULL;
    free(token);

    return tokens;
}

TokenType identify_token(char *token)
{
    if (ft_strncmp(token, "|", 1) == 0)
        return TOKEN_PIPE;
    else if (ft_strncmp(token, ">", 1) == 0)
        return TOKEN_REDIRECT_OUT;
    else if (ft_strncmp(token, "<", 1) == 0)
        return TOKEN_REDIRECT_IN;
	else if (ft_strncmp(token, ">>", 2) == 0)
		return TOKEN_APPEND_OUT;
    return TOKEN_ARG;
}

Token **classify_tokens(char **tokens)
{
    int i;
    Token **classified_tokens;
    Token *t;
    
    classified_tokens = malloc(64 * sizeof(Token*));
    i = 0;
    if (tokens[i] != NULL) {
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
/////////////////////////////////////////////////////////

Command *build_command_tree(Token **tokens)
{
    Command *root = NULL;
    Command *current = NULL;

    int i = 0;
    while (tokens[i] != NULL) {
        if (tokens[i]->type == TOKEN_COMMAND) {
            Command *new_cmd = malloc(sizeof(Command));
            new_cmd->command = tokens[i]->value;
            new_cmd->args = malloc(64 * sizeof(char*));
            new_cmd->redirect_out = NULL;
            new_cmd->redirect_in = NULL;
            new_cmd->next = NULL;

            // Adiciona argumentos ao comando
            int arg_index = 0;
            while (tokens[i + 1] != NULL && tokens[i + 1]->type == TOKEN_ARG) {
                new_cmd->args[arg_index++] = tokens[++i]->value;
            }
            new_cmd->args[arg_index] = NULL;

            // Adiciona o comando à árvore
            if (root == NULL) {
                root = new_cmd;
                current = root;
            } else {
                current->next = new_cmd;
                current = current->next;
            }
        } else if (tokens[i]->type == TOKEN_PIPE) {
            // O próximo comando no pipeline será adicionado na próxima iteração
        } else if (tokens[i]->type == TOKEN_REDIRECT_OUT) {
            if (current != NULL) {
                current->redirect_out = tokens[++i]->value;
            }
        }
        i++;
    }
    return root;
}

int validate_command_tree(Command *root)
{
    Command *current = root;

    while (current != NULL) {
        // Verifica se há um redirecionamento de saída e se o arquivo é acessível
        if (current->redirect_out != NULL) {
            if (access(current->redirect_out, F_OK) == -1) {
                fprintf(stderr, "Erro: Arquivo %s não encontrado para saída\n", current->redirect_out);
                return (0);
            }
        }

        // Verifica redirecionamento de entrada
        if (current->redirect_in != NULL) {
            if (access(current->redirect_in, R_OK) == -1) {
                fprintf(stderr, "Erro: Arquivo %s não encontrado para entrada\n", current->redirect_in);
                return (0);
            }
        }

        // Verifica se o comando é válido (ex: no caso de comandos internos do shell)
        if (current->command == NULL || current->args == NULL) {
            fprintf(stderr, "Erro: Comando inválido\n");
            return (0);
        }

        current = current->next;
    }

    return (1);
}