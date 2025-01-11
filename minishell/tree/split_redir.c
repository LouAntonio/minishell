/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 18:22:32 by hmateque          #+#    #+#             */
/*   Updated: 2024/12/14 18:22:33 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	update_prev_and_after(t_node *redir, t_node *after)
{
	redir->prev->next = after;
	after->prev->next = NULL;
	after->prev = redir->prev;
}

void	update_after(t_node *after, t_node **ptr_list, t_node **list)
{
	after->prev->next = NULL;
	after->prev = NULL;
	*list = after;
	ptr_list[0] = *list;
}

static int	check_next_char(char next_char)
{
	if (next_char != ' ' && next_char != '\t' && next_char != '\n')
		return (1);
	return (0);
}

t_node	**split_redir(t_node *list, t_node **ptr_list, t_node *redir)
{
	t_node	*file;
	t_node	*after;

	ptr_list[0] = list;
	ptr_list[1] = redir;
	ptr_list[2] = redir->next;
	after = NULL;
	file = redir->next;
	while (file && check_next_char(file->next_char) && file->next
		&& file->next->type > HEREDOC)
		file = file->next;
	if (file && file->next)
		after = file->next;
	if (redir->prev && after)
		update_prev_and_after(redir, after);
	else if (after)
		update_after(after, ptr_list, &list);
	else if (redir->prev)
		redir->prev->next = NULL;
	else
		ptr_list[0] = NULL;
	redir->next->prev = NULL;
	redir->prev = NULL;
	redir->next = NULL;
	return (ptr_list);
}
