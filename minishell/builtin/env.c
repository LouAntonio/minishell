/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 18:16:28 by hmateque          #+#    #+#             */
/*   Updated: 2024/12/14 18:16:31 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	env(t_node *list, char **env_table)
{
	int		i;
	int		status;
	char	**args;

	status = EXIT_SUCCESS;
	list = list->next;
	if (list)
		error_builtin("env doesn't accept arguments or flag\n", &status);
	else
	{
		i = 0;
		while (env_table[i])
		{
			args = find_key_value(env_table[i]);
			if (args && getenv(args[0]))
				printf("%s\n", env_table[i]);
			i++;
		}
	}
	return (status);
}
