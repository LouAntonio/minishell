/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_manipulation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:08:30 by hmateque          #+#    #+#             */
/*   Updated: 2024/12/11 11:57:48 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_list_add_back(t_env **lst, t_env *new)
{
	t_env	*t;

	if (!lst || !new)
		return ;
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
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}

void	print_list(t_env *list, int flag)
{
	if (!list)
		return ;
	if (flag == 1)
	{
		while (list != NULL)
		{
			if (ft_strcmp(list->value, "") != 0 && list->value != NULL)
				printf("%s=%s\n", list->name, list->value);
			list = list->next;
		}
	}
	else if (flag == 2)
	{
		while (list != NULL)
		{
			if (ft_strcmp(list->value, "") == 0)
				printf("%s\n", list->name);
			else
				printf("%s=%s\n", list->name, list->value);
			list = list->next;
		}
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
			ft_putstr_fd(list->value, fd);
			return ;
		}
		list = list->next;
	}
}
