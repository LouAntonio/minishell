/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:10:13 by lantonio          #+#    #+#             */
/*   Updated: 2024/11/19 15:03:08 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	pwd(char **str, int *g_returns)
{
	char	path[PATH_MAX];

	(void)str;
	if (getcwd(path, sizeof(path)) != NULL)
		printf("%s\n", path);
	else
	{
		printf("Erro ao obter o diretório\n");
		*g_returns = 0;
	}
	*g_returns = 1;
}
