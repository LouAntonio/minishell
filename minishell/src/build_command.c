/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 11:35:13 by hmateque          #+#    #+#             */
/*   Updated: 2024/12/04 08:58:57 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

#define MAX_ARGS 1000


// Protótipos de funções
Command *create_command(void);
int add_argument(Command *cmd, const char *arg);
int handle_redirection_2(Command **current, Token **tokens, int *i, int word_count);
void free_command(Command *cmd);
void free_command_tree_2(Command *root);

Command *build_command_tree(Token **tokens, int word_count)
{
    int i = 0;
    Command *root = NULL;
    Command *current = NULL;

    while (i < word_count)
    {
        if (tokens[i]->type == TOKEN_COMMAND || current == NULL)
        {
            Command *new_cmd = create_command();
            if (!new_cmd)
            {
                free_command_tree_2(root);
                return NULL;
            }

            if (tokens[i]->type == TOKEN_COMMAND)
            {
                new_cmd->command = strdup(tokens[i]->value);
                if (!new_cmd->command || !add_argument(new_cmd,""))
                {
                    free_command(new_cmd);
                    free_command_tree_2(root);
                    return NULL;
                }
                i++;
                while (tokens[i] && tokens[i]->type == TOKEN_ARG)
                {
                    if (!add_argument(new_cmd, tokens[i]->value))
                    {
                        free_command(new_cmd);
                        free_command_tree_2(root);
                        return NULL;
                    }
                    i++;
                }
            }

            if (!root)
                root = new_cmd;
            else
                current->next = new_cmd;
            current = new_cmd;
        }
        else if (tokens[i]->type >= TOKEN_REDIRECT_OUT && tokens[i]->type <= TOKEN_HEREDOC)
        {
            if (!handle_redirection_2(&current, tokens, &i, word_count))
            {
                free_command_tree_2(root);
                return NULL;
            }
        }
        i++;
    }
    return root;
}

Command *create_command(void)
{
    Command *cmd = malloc(sizeof(Command));
    if (!cmd)
        return NULL;

    cmd->command = NULL;
    cmd->args = calloc(MAX_ARGS, sizeof(char *));
    if (!cmd->args)
    {
        free(cmd);
        return NULL;
    }
    cmd->redirect_out = NULL;
    cmd->redirect_in = NULL;
    cmd->redirect_out_type = 0;
    cmd->next = NULL;
    cmd->heredoc = 0;
    cmd->heredoc_end = NULL;
    return cmd;
}

int add_argument(Command *cmd, const char *arg)
{
    int i;
    for (i = 0; i < MAX_ARGS - 1 && cmd->args[i]; i++);
    if (i == MAX_ARGS - 1)
        return 0;

    cmd->args[i] = strdup(arg);
    if (!cmd->args[i])
        return 0;

    return 1;
}

int handle_redirection_2(Command **current, Token **tokens, int *i, int word_count)
{
    if (!*current)
    {
        *current = create_command();
        if (!*current)
            return 0;
    }

    switch (tokens[*i]->type)
    {
        case TOKEN_REDIRECT_OUT:
            (*current)->redirect_out_type = 1;
            break;
        case TOKEN_APPEND_OUT:
            (*current)->redirect_out_type = 2;
            break;
        case TOKEN_REDIRECT_IN:
        case TOKEN_HEREDOC:
            break;
        default:
            return 0;
    }

    if (*i + 1 >= word_count)
    {
        printf("minishell: syntax error near unexpected token `newline'\n");
        return 0;
    }

    (*i)++;
    char **target;
    switch (tokens[*i - 1]->type)
    {
        case TOKEN_REDIRECT_OUT:
        case TOKEN_APPEND_OUT:
            target = &((*current)->redirect_out);
            break;
        case TOKEN_REDIRECT_IN:
            target = &((*current)->redirect_in);
            break;
        case TOKEN_HEREDOC:
            (*current)->heredoc = 1;
            target = &((*current)->heredoc_end);
            break;
        default:
            return 0;
    }

    *target = strdup(tokens[*i]->value);
    if (!*target)
        return 0;

    return 1;
}

void free_command(Command *cmd)
{
    if (!cmd)
        return;

    free(cmd->command);
    if (cmd->args)
    {
        for (int i = 0; cmd->args[i]; i++)
            free(cmd->args[i]);
        free(cmd->args);
    }
    free(cmd->redirect_out);
    free(cmd->redirect_in);
    free(cmd->heredoc_end);
    free(cmd);
}

void free_command_tree_2(Command *root)
{
    while (root)
    {
        Command *temp = root;
        root = root->next;
        free_command(temp);
    }
}