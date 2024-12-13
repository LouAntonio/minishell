/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 09:07:32 by hmateque          #+#    #+#             */
/*   Updated: 2024/12/12 12:02:03 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_all_var(char **env)
{
	int	i;

	i = -1;
	while (env[++i] != NULL)
		printf("%s\n", env[i]);
}

t_env *find_env_var(t_env *env, const char *name)
{
    while (env)
    {
        if (strcmp(env->name, name) == 0)
            return env;
        env = env->next;
    }
    return NULL;
}
