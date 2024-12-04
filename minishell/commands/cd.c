/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 08:22:00 by lantonio          #+#    #+#             */
/*   Updated: 2024/12/04 11:15:29 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	change_oldpwd(char *path, t_env **env, int *g_returns)
{
	char	*str;
	char	**args;
	char	new_path[PATH_MAX];

	str = ft_strdup("export OLDPWD=");
	str = ft_strjoin(str, path);
	args = ft_split(str, ' ');
	ft_export(args, env, g_returns);
	free_matrix(args);
	getcwd(new_path, sizeof(new_path));
	str = ft_strdup("export PWD=");
	str = ft_strjoin(str, new_path);
	args = ft_split(str, ' ');
	ft_export(args, env, g_returns);
	free_matrix(args);
}

int	cd(char **str, int *g_returns, t_env **env)
{
	char	path[PATH_MAX];

	getcwd(path, sizeof(path));
	*g_returns = 0;
	if (matrix_len(str) == 1)
	{
		if (chdir(getenv("HOME")) != 0)
			return (perror("Erro ao mudar de diretório"), 0);
		else
			change_oldpwd(path, env, g_returns);
	}
	else if (matrix_len(str) == 2)
	{
		if (chdir(str[1]) != 0)
			return (perror("Erro ao mudar de diretório"), 0);
		else
			change_oldpwd(path, env, g_returns);
	}
	else
		return (printf("minishell: cd: too many arguments\n"), 0);
	return (1);
}
