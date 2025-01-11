/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 18:17:10 by hmateque          #+#    #+#             */
/*   Updated: 2024/12/14 18:17:16 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	export(t_node *list, char ***env_table)
{
	int		status;
	char	**args;

	status = EXIT_SUCCESS;
	list = list->next;
	if (!list)
		print_detail_table(*env_table);
	while (list)
	{
		args = find_key_value(list->value);
		if (args)
		{
			if (is_valid_var(args[0]))
				*env_table = insert_env_var(*env_table, args[0], args[1]);
			else
				error_builtin("export: not a valid identifier\n", &status);
		}
		else if (is_valid_var(list->value))
			*env_table = insert_env_var(*env_table, list->value, NULL);
		else
			error_builtin("export: not a valid identifier\n", &status);
		list = list->next;
	}
	return (status);
}

int	is_valid_var(char *str)
{
	int	i;

	i = 0;
	if ((str[i] && !ft_isalpha(str[i]) && str[i] != '_') || !str[i])
		return (0);
	i++;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	is_there_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

char	**allocate_letters(char *str)
{
	int		i;
	int		j;
	char	**args;

	args = allocate_mem(3, sizeof(char *));
	i = 0;
	while (str[i] != '=')
		i++;
	args[0] = allocate_mem(i + 1, sizeof(char));
	i++;
	j = 0;
	while (str[i])
	{
		i++;
		j++;
	}
	args[1] = allocate_mem(j + 1, sizeof(char));
	return (args);
}

char	**find_key_value(char *str)
{
	int		i;
	int		j;
	char	**args;

	if (!is_there_equal(str))
		return (NULL);
	args = allocate_letters(str);
	i = 0;
	while (str[i] != '=')
	{
		args[0][i] = str[i];
		i++;
	}
	args[0][i] = '\0';
	i++;
	j = 0;
	while (str[i])
	{
		args[1][j] = str[i];
		i++;
		j++;
	}
	args[1][j] = '\0';
	args[2] = NULL;
	return (args);
}
