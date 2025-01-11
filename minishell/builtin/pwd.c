/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 18:17:21 by hmateque          #+#    #+#             */
/*   Updated: 2024/12/14 18:17:22 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_pwd(void)
{
	char	*cwd;
	char	*buffer;
	size_t	path_max;

	path_max = 1024;
	buffer = allocate_mem(path_max, sizeof(char));
	cwd = NULL;
	while (path_max < 4096)
	{
		cwd = getcwd(buffer, path_max);
		if (cwd)
			return (cwd);
		else
		{
			path_max *= 2;
			buffer = allocate_mem(path_max, sizeof(char));
		}
	}
	if (!cwd)
	{
		cwd = update_cwd(cwd);
		if (cwd)
			return (cwd);
	}
	return (NULL);
}

int	pwd(void)
{
	char	*pwd;

	pwd = get_pwd();
	if (pwd)
	{
		ft_putendl_fd(pwd, STDOUT_FILENO);
		return (EXIT_SUCCESS);
	}
	else
	{
		perror("pwd: ");
		return (EXIT_FAILURE);
	}
}

char	**static_cwd(void)
{
	static char	*cwd;

	return (&cwd);
}

char	*update_cwd(char *new_pwd)
{
	char	**cwd;

	cwd = static_cwd();
	if (!*cwd && new_pwd)
		*cwd = ft_strdup(new_pwd);
	if (new_pwd && ft_strcmp(*cwd, new_pwd) != 0)
	{
		free(*cwd);
		*cwd = ft_strdup(new_pwd);
	}
	return (*cwd);
}
