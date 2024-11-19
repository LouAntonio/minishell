/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 14:39:54 by hmateque          #+#    #+#             */
/*   Updated: 2024/11/15 11:50:35 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	add_or_update_env(t_env **env, char *key, char *value)
{
	t_env	*temp;
	t_env	*new_node;

	temp = *env;
	while (temp)
	{
		if (strcmp(temp->name, key) == 0)
		{
			free(temp->value);
			temp->value = ft_strdup(value);
			return ;
		}
		temp = temp->next;
	}
	new_node = malloc(sizeof(t_env));
	new_node->name = ft_strdup(key);
	new_node->value = ft_strdup(value);
	new_node->next = *env;
	*env = new_node;
}

static void	add_var_of_env(char *str, t_env **env)
{
	char	*equal_sign;

	equal_sign = ft_strchr(str, '=');
	if (equal_sign)
	{
		*equal_sign = '\0';
		add_or_update_env(env, str, equal_sign + 1);
		*equal_sign = '=';
	}
	else
		add_or_update_env(env, str, "");
}

int	ft_export(char **command, t_env **env)
{
	int	len_str;

	len_str = 0;
	while (command[len_str])
		len_str++;
	if (len_str == 0)
	{
		print_list(*env, 2);
		return (1);
	}
	len_str = 1;
	while (command[len_str])
	{
		if (!check_arg(command[len_str]))
		{
			printf("export: '%s': not a valid identifier\n", command[len_str]);
			continue ;
		}
		add_var_of_env(command[len_str], env);
		len_str++;
	}
	return (0);
}
