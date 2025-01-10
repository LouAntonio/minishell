/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_aux.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 22:07:43 by lantonio          #+#    #+#             */
/*   Updated: 2025/01/10 22:49:35 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	path_commands(t_cmd *cmd, t_env **env, char **envp, int *g_returns)
{
	char	**paths;
	int		result;

	paths = get_env_paths(*env);
	if (!validate_env(env))
		return (printf("Env Error\n"), -1);
	if (is_absolute_path(cmd->command))
		return (execute_absolute_path(cmd, envp, g_returns));
	if (!paths)
		return (printf("t_cmd not found\n"), -1);
	result = try_paths(paths, cmd, envp, g_returns);
	free_matrix(paths);
	if (result == -1)
		*g_returns = 127;
	return (result);
}

bool	validate_env(t_env **env)
{
	return (*env != NULL);
}

bool	is_absolute_path(const char *command)
{
	return (command[0] == '/');
}

int	execute_absolute_path(t_cmd *cmd, char **envp, int *g_returns)
{
	if (access(cmd->command, X_OK) == 0)
		return (execute_command(cmd->command, cmd->args, envp, g_returns));
	return (printf("minishell: %s: No such file or directory\n",
			cmd->command), -1);
}

char	**get_env_paths(t_env *env)
{
	while (env)
	{
		if (!ft_strcmp(env->name, "PATH"))
		{
			if (env->value && *env->value)
				return (ft_split(env->value, ':'));
			return (NULL);
		}
		env = env->next;
	}
	return (NULL);
}
