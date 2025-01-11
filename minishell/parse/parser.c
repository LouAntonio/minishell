/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 14:45:32 by cogata            #+#    #+#             */
/*   Updated: 2025/01/11 09:20:23 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	parse(char *input, t_tree **root)
{
	t_node	*head;

	if (check_quote_syntax(input))
	{
		ft_putstr_fd("Syntax error\n", STDERR_FILENO);
		update_exit_status(2);
		return ;
	}
	head = tokenizer(input);
	if (!head)
		return ;
	if (check_syntax(head))
	{
		ft_putstr_fd("Syntax error\n", STDERR_FILENO);
		update_exit_status(2);
		return ;
	}
	check_heredoc(head);
	if (g_signal == 130)
	{
		update_exit_status(130);
		return ;
	}
	build_tree(root, head);
}
