/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 18:17:50 by hmateque          #+#    #+#             */
/*   Updated: 2024/12/14 18:17:53 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_env_table(char **env_table)
{
	int	i;

	i = 0;
	while (env_table[i])
	{
		free(env_table[i]);
		i++;
	}
	free(env_table);
}
