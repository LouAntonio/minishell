/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 18:18:01 by hmateque          #+#    #+#             */
/*   Updated: 2024/12/14 18:18:03 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**get_env_table(void)
{
	int		i;
	char	**env_table;

	i = 0;
	while (__environ[i])
		i++;
	env_table = ft_calloc(i + 1, sizeof(char *));
	i = 0;
	while (__environ[i])
	{
		env_table[i] = ft_strdup(__environ[i]);
		i++;
	}
	env_table[i] = NULL;
	return (env_table);
}
