/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 11:35:13 by hmateque          #+#    #+#             */
/*   Updated: 2025/01/11 00:36:54 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	process_heredoc(t_token **tokens, int *i, t_cmd *current)
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

void	process_command_args(t_token **tokens, int *i, t_cmd *cmd, int *index)
{
	while (tokens[*i + 1] != NULL && tokens[*i + 1]->type == TOKEN_ARG)
	{
		if (*index == 0)
			cmd->args[(*index)++] = cmd->command;
		else
			cmd->args[(*index)++] = tokens[++(*i)]->value;
	}
}

t_cmd	*handle_new_cmd(t_cmd **root,
	t_cmd *cur, t_token *token, int wc)
{
	t_cmd	*new_cmd;

	new_cmd = initialize_command(wc);
	if (new_cmd == NULL)
		return (NULL);
	if (token->type == TOKEN_COMMAND)
		new_cmd->command = token->value;
	if (*root == NULL)
		*root = new_cmd;
	else
		cur->next = new_cmd;
	return (new_cmd);
}

int	handle_redirections(t_token **tokens, int *i, t_cmd *current)
{
	if (tokens[*i]->type == TOKEN_REDIRECT_OUT)
		return (process_redirect_out(tokens, i, current));
	else if (tokens[*i]->type == TOKEN_APPEND_OUT)
		return (process_append_out(tokens, i, current));
	else if (tokens[*i]->type == TOKEN_REDIRECT_IN)
		return (process_redirect_in(tokens, i, current));
	else if (tokens[*i]->type == TOKEN_HEREDOC)
		return (process_heredoc(tokens, i, current));
	return (1);
}

t_cmd	*build_cmd(t_token **tokens, int wordcount)
{
	int		i;
	int		arg_index;
	t_cmd	*root;
	t_cmd	*current;

	i = 0;
	root = NULL;
	current = NULL;
	while (tokens[i] != NULL)
	{
		if (tokens[i]->type == TOKEN_COMMAND || current == NULL)
		{
			current = handle_new_cmd(&root, current, tokens[i], wordcount);
			if (current == NULL)
				return (NULL);
			arg_index = 0;
		}
		if (!handle_redirections(tokens, &i, current))
			return (NULL);
		process_command_args(tokens, &i, current, &arg_index);
		i++;
	}
	return (root);
}
