/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_file2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 22:29:41 by lantonio          #+#    #+#             */
/*   Updated: 2025/01/10 22:49:35 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_cmd	*initialize_command(int wordcount)
{
	t_cmd	*new_cmd;

	new_cmd = malloc(sizeof(t_cmd));
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

int	process_redirect_out(t_token **tokens, int *i, t_cmd *current)
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

int	process_append_out(t_token **tokens, int *i, t_cmd *current)
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

int	process_redirect_in(t_token **tokens, int *i, t_cmd *current)
{
	if (tokens[*i + 1])
	{
		current->redirect_in = tokens[++(*i)]->value;
		return (1);
	}
	printf("minishell: syntax error near unexpected token `newline 3'\n");
	return (0);
}
