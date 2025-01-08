/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 11:35:13 by hmateque          #+#    #+#             */
/*   Updated: 2025/01/07 14:25:11 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

Command	*initialize_command(int wordcount)
{
	Command	*new_cmd;

	new_cmd = malloc(sizeof(Command));
	collect_mem(new_cmd, MEM_COMMAND, 0);
	new_cmd->command = NULL;
	new_cmd->args = ft_calloc((wordcount + 1), sizeof(char *));
	collect_mem(new_cmd->args, MEM_CHAR_MATRIX, matrix_len(new_cmd->args));
	new_cmd->redirect_out = NULL;
	new_cmd->redirect_in = NULL;
	new_cmd->redirect_out_type = 0;
	new_cmd->next = NULL;
	new_cmd->heredoc = 0;
	new_cmd->heredoc_end = NULL;
	return (new_cmd);
}

int	process_redirect_out(Token **tokens, int *i, Command *current)
{
	current->redirect_out_type = 1;
	if (tokens[*i + 1])
	{
		current->redirect_out = tokens[++(*i)]->value;
		return (1);
	}
	printf("minishell: syntax error near unexpected token `newline 1'\n");
	return (0);
}

int	process_append_out(Token **tokens, int *i, Command *current)
{
	current->redirect_out_type = 2;
	if (tokens[*i + 1])
	{
		current->redirect_out = tokens[++(*i)]->value;
		return (1);
	}
	printf("minishell: syntax error near unexpected token `newline 2'\n");
	return (0);
}

int	process_redirect_in(Token **tokens, int *i, Command *current)
{
	if (tokens[*i + 1])
	{
		current->redirect_in = tokens[++(*i)]->value;
		return (1);
	}
	printf("minishell: syntax error near unexpected token `newline 3'\n");
	return (0);
}

int	process_heredoc(Token **tokens, int *i, Command *current)
{
	if (tokens[*i + 1])
	{
		current->heredoc = 1;
		current->heredoc_end = tokens[++(*i)]->value;
		return (1);
	}
	printf("minishell: syntax error near unexpected token `newline 4'\n");
	return (0);
}

void	process_command_args(Token **tokens, int *i, Command *cmd, int *index)
{
	while (tokens[*i + 1] != NULL && tokens[*i + 1]->type == TOKEN_ARG)
	{
		if (*index == 0)
			cmd->args[(*index)++] = cmd->command;
		else
			cmd->args[(*index)++] = tokens[++(*i)]->value;
	}
}

Command	*build_cmd(Token **tokens, int wordcount)
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
		if (tokens[i]->type == TOKEN_COMMAND || current == NULL)
		{
			new_cmd = initialize_command(wordcount);
			arg_index = 0;
			if (tokens[i]->type == TOKEN_COMMAND)
				new_cmd->command = tokens[i]->value;
			if (root == NULL)
				root = new_cmd;
			else
				current->next = new_cmd;
			current = new_cmd;
		}
		if (tokens[i]->type == TOKEN_REDIRECT_OUT)
		{
			if (!process_redirect_out(tokens, &i, current))
				return (NULL);
		}
		else if (tokens[i]->type == TOKEN_APPEND_OUT)
		{
			if (!process_append_out(tokens, &i, current))
				return (NULL);
		}
		else if (tokens[i]->type == TOKEN_REDIRECT_IN)
		{
			if (!process_redirect_in(tokens, &i, current))
				return (NULL);
		}
		else if (tokens[i]->type == TOKEN_HEREDOC)
		{
			if (!process_heredoc(tokens, &i, current))
				return (NULL);
		}
		process_command_args(tokens, &i, current, &arg_index);
		i++;
	}
	return (root);
}
