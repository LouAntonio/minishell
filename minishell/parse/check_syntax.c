/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 18:21:20 by hmateque          #+#    #+#             */
/*   Updated: 2024/12/14 18:21:20 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_quote_syntax(char *input)
{
	int		inside_quote;
	char	quote_type;

	inside_quote = 0;
	quote_type = '\0';
	while (*input)
	{
		if (*input == '"' || *input == '\'')
		{
			if (!inside_quote)
			{
				inside_quote = 1;
				quote_type = *input;
			}
			else if (*input == quote_type)
			{
				inside_quote = 0;
				quote_type = '\0';
			}
		}
		input++;
	}
	if (inside_quote)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	check_par_syntax(int par_count, t_node *node)
{
	while (node)
	{
		if (par_count < 0)
			return (EXIT_FAILURE);
		if (node->type == OPEN_PAR)
			par_count++;
		else if (node->type == CLOSE_PAR)
			par_count--;
		node = node->next;
	}
	if (par_count != 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	par_check(t_node *node)
{
	if (node->type == OPEN_PAR)
	{
		if (node->next->type == CLOSE_PAR || (node->next->type >= AND
				&& node->next->type <= PIPE))
			return (EXIT_FAILURE);
		if (node->next->type >= AND && node->next->type <= PIPE
			&& (node->next->next->type == OPEN_PAR
				|| node->next->next->type == CLOSE_PAR))
			return (EXIT_FAILURE);
	}
	if (node->type == CLOSE_PAR)
	{
		if (node->prev->type >= AND && node->prev->type <= PIPE)
			return (EXIT_FAILURE);
		if (node->next->type >= WORD && node->next->type <= OPEN_PAR)
			return (EXIT_FAILURE);
		if ((node->next->type >= AND && node->next->type <= PIPE)
			&& (node->next->next) && !(node->next->next->type >= WORD
				&& node->next->next->type <= OPEN_PAR))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	error_check(t_node *node)
{
	if (node->type >= AND && node->type <= PIPE)
	{
		if (node->next->type >= AND && node->next->type <= PIPE)
			return (EXIT_FAILURE);
	}
	if (node->type >= IN_REDIR && node->type <= HEREDOC)
	{
		if (node->next->type >= AND && node->next->type <= HEREDOC)
			return (EXIT_FAILURE);
	}
	if (par_check(node))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	check_syntax(t_node *node)
{
	t_node	*tmp;

	tmp = node;
	if (node->type >= AND && node->type <= PIPE)
		return (EXIT_FAILURE);
	while (node->next)
	{
		if (error_check(node))
			return (EXIT_FAILURE);
		node = node->next;
	}
	if (node->type >= AND && node->type <= HEREDOC)
		return (EXIT_FAILURE);
	if (check_par_syntax(0, tmp))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
