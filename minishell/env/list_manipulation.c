/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_manipulation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:08:30 by hmateque          #+#    #+#             */
/*   Updated: 2024/10/30 16:41:36 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"

void	ft_list_add_back(t_env **lst, t_env *new)
{
	t_env	*t;

	if (*lst)
	{
		t = ft_list_last(*lst);
		t->next = new;
	}
	else
		*lst = new;
}

t_env	*ft_list_last(t_env *lst)
{
	if (lst == NULL)
		return (0);
	while (lst)
	{
		if (lst->next == NULL)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

void	print_list(t_env *list)
{
	if (!list)
		return ;
	while (list != NULL)
	{
		printf("%s = %s\n", list->name, list->value);
		list = list->next;
	}
}

void	search_and_print_list(t_env *list, char *str, int fd)
{
	(void)fd;
	if (!list)
		return ;
	while (list != NULL)
	{
		if (ft_strcmp(list->name, str) == 0)
		{
			printf("%s = %s\n", list->name, list->value);
			return ;
		}
		list = list->next;
	}
}