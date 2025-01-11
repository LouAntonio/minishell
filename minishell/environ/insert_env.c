/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 18:18:16 by hmateque          #+#    #+#             */
/*   Updated: 2024/12/14 18:18:17 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**insert_env_var(char **env_table, char *key, char *value)
{
	if (value)
		env_table = insert_if_has_value(env_table, key, value);
	else
		env_table = insert_if_has_no_value(env_table, key);
	__environ = env_table;
	return (env_table);
}

char	**insert_if_has_value(char **env_table, char *key, char *value)
{
	char	*var;
	char	*var_new_line;
	char	*var_old_line;

	var = ft_strjoin(key, "=");
	var_new_line = ft_strjoin(var, value);
	if (getenv(key) && (getenv(key))[0])
	{
		var_old_line = ft_strjoin(var, getenv(key));
		env_table = modify_env_var(env_table, var_new_line, var_old_line);
	}
	else if (getenv(key))
	{
		var_old_line = ft_strjoin(key, "=");
		env_table = modify_env_var(env_table, var_new_line, var_old_line);
	}
	else if (find_key(key, env_table))
	{
		var_old_line = ft_strdup(key);
		env_table = modify_env_var(env_table, var_new_line, var_old_line);
	}
	else
		env_table = add_env_var(env_table, var_new_line);
	free(var);
	return (env_table);
}

char	**insert_if_has_no_value(char **env_table, char *key)
{
	char	*var_new_line;

	var_new_line = ft_strdup(key);
	if (!find_key(key, env_table))
		env_table = add_env_var(env_table, var_new_line);
	else
		free(var_new_line);
	return (env_table);
}

char	**modify_env_var(char **env_table, char *var_new_line,
		char *var_old_line)
{
	int		i;
	int		size;
	char	**new_table;

	size = 0;
	while (env_table[size])
		size++;
	new_table = ft_calloc(size + 1, sizeof(char *));
	i = 0;
	while (env_table[i])
	{
		if (ft_strncmp(env_table[i], var_old_line,
				ft_strlen(env_table[i])) == 0)
			new_table[i] = ft_strdup(var_new_line);
		else
			new_table[i] = ft_strdup(env_table[i]);
		i++;
	}
	free(var_new_line);
	free(var_old_line);
	collect_env_mem(new_table);
	return (new_table);
}

char	**add_env_var(char **env_table, char *var_line)
{
	char	**new_table;
	int		i;
	int		size;

	size = 0;
	while (env_table[size])
		size++;
	new_table = ft_calloc(size + 2, sizeof(char *));
	if (!new_table)
		return (NULL);
	i = 0;
	while (i < size)
	{
		new_table[i] = ft_strdup(env_table[i]);
		i++;
	}
	new_table[i] = ft_strdup(var_line);
	free(var_line);
	new_table[i + 1] = NULL;
	__environ = new_table;
	collect_env_mem(new_table);
	return (new_table);
}
