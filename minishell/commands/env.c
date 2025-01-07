/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 11:02:37 by lantonio          #+#    #+#             */
/*   Updated: 2025/01/07 14:20:37 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_env(char **args, int *g_returns, t_env **env)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	if (i != 0)
	{
		*g_returns = 127;
		printf("env: '%s': No such file or directory\n", args[1]);
		return ;
	}
	*g_returns = 0;
	print_list(*env, 1);
}
