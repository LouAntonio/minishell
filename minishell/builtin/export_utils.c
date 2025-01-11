/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 18:17:03 by hmateque          #+#    #+#             */
/*   Updated: 2024/12/14 18:17:05 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*add_quote_and_join(char *str)
{
	int		i;
	int		j;
	char	*new_string;
	char	**args;

	args = find_key_value(str);
	if (!args && str)
		return (str);
	new_string = allocate_mem(ft_strlen(str) + 3, sizeof(char));
	i = 0;
	while (args[0][i])
	{
		new_string[i] = args[0][i];
		i++;
	}
	new_string[i++] = '=';
	new_string[i++] = '"';
	j = 0;
	while (args[1][j])
		new_string[i++] = args[1][j++];
	new_string[i++] = '"';
	new_string[i] = '\0';
	return (new_string);
}

char	**copy_table(char **original)
{
	int		i;
	char	**copy_table;
	char	*new_string;

	i = 0;
	copy_table = NULL;
	while (original[i])
		i++;
	copy_table = allocate_mem(i + 1, sizeof(char *));
	i = 0;
	while (original[i])
	{
		new_string = add_quote_and_join(original[i]);
		copy_table[i] = new_string;
		i++;
	}
	copy_table[i] = NULL;
	return (copy_table);
}

int	current_is_first(char *current, char *next)
{
	int	i;

	i = 0;
	while (current[i] && next[i] && current[i] != '=' && next[i] != '=')
	{
		if (current[i] < next[i])
			return (1);
		else if (current[i] > next[i])
			return (0);
		i++;
	}
	if (current[i] && current[i] == '=')
		return (1);
	else if (current[i])
		return (0);
	else
		return (1);
}

void	ordenate_table(char **table)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (table[i])
	{
		j = i + 1;
		while (table[j])
		{
			if (!current_is_first(table[i], table[j]))
			{
				temp = table[i];
				table[i] = table[j];
				table[j] = temp;
			}
			j++;
		}
		i++;
	}
}

void	print_detail_table(char **env_table)
{
	int		i;
	char	**table;

	table = copy_table(env_table);
	ordenate_table(table);
	i = 0;
	while (table[i])
	{
		printf("declare -x %s\n", table[i]);
		i++;
	}
}
