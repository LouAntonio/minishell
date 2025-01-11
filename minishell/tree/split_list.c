/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 18:22:26 by hmateque          #+#    #+#             */
/*   Updated: 2024/12/14 18:22:26 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_node	**split_list(t_node *list)
{
	t_node	*last;
	t_node	*operator;
	t_node	**ptr_list;
	t_node	*redir;

	last = last_node(list);
	operator = lookfor_operator(last);
	redir = lookfor_redir(list);
	if (!redir && !operator && list)
		return (NULL);
	ptr_list = allocate_mem(3, sizeof(t_node *));
	if (operator)
	{
		ptr_list[0] = list;
		ptr_list[1] = operator;
		ptr_list[2] = operator->next;
		operator->prev->next = NULL;
		operator->prev = NULL;
		operator->next->prev = NULL;
		operator->next = NULL;
	}
	else if (redir)
		ptr_list = split_redir(list, ptr_list, redir);
	return (ptr_list);
}

t_node	*lookfor_operator(t_node *last)
{
	t_node	*cur;

	cur = lookfor_and_or(last);
	if (cur)
		return (cur);
	cur = lookfor_pipe(last);
	if (cur)
		return (cur);
	return (NULL);
}

t_node	*lookfor_and_or(t_node *last)
{
	t_node	*cur;
	int		inside_par;

	cur = last;
	inside_par = 0;
	while (cur->prev)
	{
		if (cur->type == CLOSE_PAR)
			inside_par++;
		else if (cur->type == OPEN_PAR)
			inside_par--;
		else if (!inside_par && (cur->type == AND || cur->type == OR))
			return (cur);
		cur = cur->prev;
	}
	return (NULL);
}

t_node	*lookfor_pipe(t_node *last)
{
	t_node	*cur;
	int		inside_par;

	cur = last;
	inside_par = 0;
	while (cur->prev)
	{
		if (cur->type == CLOSE_PAR)
			inside_par++;
		else if (cur->type == OPEN_PAR)
			inside_par--;
		else if (!inside_par && cur->type == PIPE)
			return (cur);
		cur = cur->prev;
	}
	return (NULL);
}

t_node	*lookfor_redir(t_node *list)
{
	t_node	*cur;
	int		inside_par;

	cur = list;
	inside_par = 0;
	while (cur->next)
	{
		if (cur->type == OPEN_PAR)
			inside_par++;
		else if (cur->type == CLOSE_PAR)
			inside_par--;
		else if (!inside_par && cur->type >= IN_REDIR && cur->type <= HEREDOC)
			return (cur);
		cur = cur->next;
	}
	return (NULL);
}
