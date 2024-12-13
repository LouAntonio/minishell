/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 11:35:13 by hmateque          #+#    #+#             */
/*   Updated: 2024/12/13 10:43:02 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

Command	*build_command_tree(Token **tokens, int wordcount)
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
			new_cmd = malloc(sizeof(Command));
			new_cmd->command = tokens[i]->value;
			new_cmd->args = ft_calloc((wordcount + 1), sizeof(char *));
			new_cmd->redirect_out = NULL;
			new_cmd->redirect_in = NULL;
			new_cmd->redirect_out_type = 0;
			new_cmd->next = NULL;
			new_cmd->heredoc = 0;
			new_cmd->heredoc_end = NULL;
			arg_index = 0;
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
		if (tokens[i]->type == TOKEN_REDIRECT_OUT)
		{
			if (current == NULL)
			{
				new_cmd = malloc(sizeof(Command));
				new_cmd->command = NULL;
				new_cmd->args = NULL;
				new_cmd->redirect_out = NULL;
				new_cmd->redirect_in = NULL;
				new_cmd->redirect_out_type = 0;
				new_cmd->next = NULL;
				new_cmd->heredoc = 0;
				new_cmd->heredoc_end = NULL;
				if (root == NULL)
					root = new_cmd;
				current = new_cmd;
			}
			current->redirect_out_type = 1;
			if (tokens[i + 1])
				current->redirect_out = tokens[++i]->value;
			else
				return (printf("minishell: syntax error near unexpected token `newline 1'\n"), NULL);
		}
		else if (tokens[i]->type == TOKEN_APPEND_OUT)
		{
			if (current == NULL)
			{
				new_cmd = malloc(sizeof(Command));
				new_cmd->command = NULL;
				new_cmd->args = NULL;
				new_cmd->redirect_out = NULL;
				new_cmd->redirect_in = NULL;
				new_cmd->redirect_out_type = 0;
				new_cmd->next = NULL;
				new_cmd->heredoc = 0;
				new_cmd->heredoc_end = NULL;
				if (root == NULL)
					root = new_cmd;
				current = new_cmd;
			}
			current->redirect_out_type = 2;
			if (tokens[i + 1])
				current->redirect_out = tokens[++i]->value;
			else
				return (printf("minishell: syntax error near unexpected token `newline 2'\n"), NULL);
		}
		else if (tokens[i]->type == TOKEN_REDIRECT_IN)
		{
			if (current == NULL)
			{
				new_cmd = malloc(sizeof(Command));
				new_cmd->command = NULL;
				new_cmd->args = NULL;
				new_cmd->redirect_out = NULL;
				new_cmd->redirect_in = NULL;
				new_cmd->redirect_out_type = 0;
				new_cmd->next = NULL;
				new_cmd->heredoc = 0;
				new_cmd->heredoc_end = NULL;
				if (root == NULL)
					root = new_cmd;
				current = new_cmd;
			}
			if (tokens[i + 1])
				current->redirect_in = tokens[++i]->value;
			else
				return (printf("minishell: syntax error near unexpected token `newline 3'\n"), NULL);
		}
		else if (tokens[i]->type == TOKEN_HEREDOC)
		{
			if (current == NULL)
			{
				new_cmd = malloc(sizeof(Command));
				new_cmd->command = NULL;
				new_cmd->args = NULL;
				new_cmd->redirect_out = NULL;
				new_cmd->redirect_in = NULL;
				new_cmd->redirect_out_type = 0;
				new_cmd->next = NULL;
				new_cmd->heredoc = 0;
				new_cmd->heredoc_end = NULL;
				if (root == NULL)
					root = new_cmd;
				current = new_cmd;
			}
			if (tokens[i + 1])
			{
				current->heredoc = 1;
				current->heredoc_end = tokens[++i]->value;
			}
			else
				return (printf("minishell: syntax error near unexpected token `newline 4'\n"), NULL);
		}
		while (tokens[i + 1] != NULL && tokens[i + 1]->type == TOKEN_ARG)
			if (arg_index == 0)
				new_cmd->args[arg_index++] = new_cmd->command;
			else
				new_cmd->args[arg_index++] = tokens[++i]->value;
		i++;
	}
	return (root);
}
