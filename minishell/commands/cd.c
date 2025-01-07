/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 08:22:00 by lantonio          #+#    #+#             */
/*   Updated: 2025/01/07 12:05:06 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void change_oldpwd(char *path, t_env **env, int *g_returns)
{
    char    *str;
    char    *temp;
    char    **args;
    char    new_path[PATH_MAX];

    str = ft_strdup("export OLDPWD=");
    if (!str)
        return;
    temp = str;
    str = ft_strjoin(str, path);
    free(temp);
    if (!str)
        return;
    args = ft_split(str, ' ');
    if (!args)
    {
        free(str);
        return;
    }
    ft_export(args, env, g_returns);
    free(str);
    free_matrix(args);
    if (getcwd(new_path, sizeof(new_path)) == NULL)
        return;
    str = ft_strdup("export PWD=");
    if (!str)
        return;
    temp = str;
    str = ft_strjoin(str, new_path);
    free(temp);
    if (!str)
        return;
    args = ft_split(str, ' ');
    if (!args)
    {
        free(str);
        return;
    }
    ft_export(args, env, g_returns);
    free(str);
    free_matrix(args);
}

int	cd(char **str, int *g_returns, t_env **env)
{
	t_env	*env_cpy;
	char	path[PATH_MAX];

	env_cpy = *env;
	while (env_cpy)
	{
		if (!ft_strcmp(env_cpy->name, "HOME"))
			break ;
		env_cpy = env_cpy->next;
	}
	if (!env_cpy->value || !*env_cpy->value)
		return (printf("Command not found\n"), 0);
	getcwd(path, sizeof(path));
	*g_returns = 0;
	printf("HOME = %s\n", env_cpy->value);
	if (matrix_len(str) == 0)
	{
		if (chdir(env_cpy->value) != 0)
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
