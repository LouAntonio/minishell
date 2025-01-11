/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 18:15:49 by hmateque          #+#    #+#             */
/*   Updated: 2024/12/14 18:15:55 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	check_access(char *path)
{
	if (access(path, F_OK))
	{
		ft_putendl_fd("cd: No such file or directory", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	else if (access(path, R_OK))
	{
		ft_putendl_fd("cd: Permission denied", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	change_dir(char *path, char ***env_table)
{
	char	*cur_dir;

	if (check_access(path))
		return (EXIT_FAILURE);
	cur_dir = get_pwd();
	if (!cur_dir)
	{
		perror("cd");
		free(cur_dir);
		return (EXIT_FAILURE);
	}
	if (chdir(path) == -1)
	{
		perror("cd");
		return (EXIT_FAILURE);
	}
	*env_table = insert_env_var(*env_table, "OLDPWD", cur_dir);
	*env_table = insert_env_var(*env_table, "PWD", get_pwd());
	update_cwd(get_pwd());
	return (EXIT_SUCCESS);
}

static int	change_to_home(char ***env_table)
{
	char	*home;

	home = getenv("HOME");
	if (home)
	{
		chdir(getenv("HOME"));
		*env_table = insert_env_var(*env_table, "OLDPWD", home);
		*env_table = insert_env_var(*env_table, "PWD", get_pwd());
		return (EXIT_SUCCESS);
	}
	else
	{
		ft_putendl_fd("cd: HOME not set", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
}

int	cd(t_node *list, char ***env_table)
{
	char	**args;

	args = list_to_array(list);
	if (!args[1] || (args[1] && !args[2] && !ft_strcmp(args[1], "~")))
		return (change_to_home(env_table));
	else if (args[2])
	{
		ft_putendl_fd("cd: too many arguments", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	return (change_dir(args[1], env_table));
}
