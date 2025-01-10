/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 08:23:31 by hmateque          #+#    #+#             */
/*   Updated: 2025/01/10 23:42:05 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_env_list(t_env **env)
{
	t_env	*current;
	t_env	*next;

	if (!env || !*env)
		return ;
	current = *env;
	while (current)
	{
		next = current->next;
		free(current->name);
		free(current->value);
		free(current);
		current = next;
	}
	*env = NULL;
}

int	is_all_digits(const char *str)
{
	if (str == NULL || *str == '\0')
		return (0);
	while (*str)
	{
		if (!ft_isdigit((int)*str))
			return (0);
		str++;
	}
	return (1);
}

void	exit_and_return(char *exit_status)
{
	int		int_ret;

	if (!exit_status)
		exit(0);
	if (exit_status[0] == '\0' || !exit_status)
		(free(exit_status), exit(0));
	if (!is_all_digits(exit_status))
	{
		printf("bash: exit: %s: numeric argument required", exit_status);
		(free(exit_status), exit(2));
	}
	int_ret = ft_atoi(exit_status);
	if (int_ret < 0 || int_ret > 255)
		(free(exit_status), exit(int_ret % 256));
	if (int_ret < INT_MIN || int_ret > INT_MAX)
		(free(exit_status), exit(2));
	(free(exit_status), exit(0));
}

void	ft_exit(t_env **env, int status, char *exit_status)
{
	char	*ret;

	if (!exit_status)
		ret = ft_strdup("");
	else
		ret = ft_strdup(exit_status);
	free_env_list(env);
	if (status == 1)
		free_all_mem();
	ft_putstr_fd("exit\n", 1);
	exit_and_return(ret);
}

void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	if (!matrix)
		return ;
	while (matrix[i] != NULL)
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}
