/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 08:19:38 by hmateque          #+#    #+#             */
/*   Updated: 2024/11/19 08:13:14 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_free_node(t_env *temp)
{
	free(temp->name);
	free(temp->value);
	free(temp);
}

static void	delete_env(t_env **env, char *key)
{
	t_env	*temp;
	t_env	*prev;

	temp = *env;
	prev = NULL;
	if (temp && strcmp(temp->name, key) == 0)
	{
		*env = temp->next;
		ft_free_node(temp);
		return ;
	}
	while (temp && strcmp(temp->name, key) != 0)
	{
		prev = temp;
		temp = temp->next;
	}
	if (!temp)
		return ;
	prev->next = temp->next;
	ft_free_node(temp);
}

int	ft_unset(char **command, t_env **env)
{
	int	len_str;

	len_str = 0;
	while (command[len_str])
		len_str++;
	if (len_str == 1)
		return (printf("unset: not enough arguments\n"), 1);
	len_str = 1;
	while (command[len_str])
	{
		if (!check_arg(command[len_str]))
			continue ;
		delete_env(env, command[len_str]);
		len_str++;
	}
	return (0);
}
