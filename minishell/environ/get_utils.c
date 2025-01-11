/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 18:18:10 by hmateque          #+#    #+#             */
/*   Updated: 2024/12/14 18:18:11 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	compare_var(char *s1, char *s2)
{
	int	i;

	i = 0;
	while ((s1[i] && s1[i] != '=') || (s2[i] && s2[i] != '='))
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	if ((s1[i] == s2[i]) || (!s1[i] && s2[i] == '=') || (!s2[i]
			&& s1[i] == '='))
		return (1);
	return (0);
}

int	find_key(char *key, char **env_table)
{
	int	i;

	i = 0;
	while (env_table[i])
	{
		if (compare_var(key, env_table[i]) == 1)
			return (1);
		i++;
	}
	return (0);
}
