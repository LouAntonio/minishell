/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 18:17:43 by hmateque          #+#    #+#             */
/*   Updated: 2024/12/14 18:17:45 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**del_env_var(char **env_table, char *key)
{
	int		size;
	char	*var_equal;
	char	*var_line;
	char	**new_env_table;

	if (getenv(key))
	{
		var_equal = ft_strjoin(key, "=");
		var_line = ft_strjoin(var_equal, getenv(key));
		free(var_equal);
	}
	else if (find_key(key, env_table))
		var_line = ft_strdup(key);
	else
		return (env_table);
	size = 0;
	while (env_table[size])
		size++;
	new_env_table = update_env_table(env_table, var_line, size);
	__environ = new_env_table;
	collect_env_mem(new_env_table);
	return (new_env_table);
}

char	**update_env_table(char **env_table, char *var_line, int size)
{
	int		i;
	int		j;
	char	**new_env_table;

	new_env_table = ft_calloc(size, sizeof(char *));
	i = 0;
	j = 0;
	while (env_table[i])
	{
		if (ft_strncmp(env_table[i], var_line, ft_strlen(env_table[i])) == 0)
			i++;
		if (!env_table[i])
			break ;
		new_env_table[j] = ft_strdup(env_table[i]);
		i++;
		j++;
	}
	new_env_table[j] = NULL;
	free(var_line);
	return (new_env_table);
}
