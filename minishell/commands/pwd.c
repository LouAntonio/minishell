/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:10:13 by lantonio          #+#    #+#             */
/*   Updated: 2024/11/27 08:51:21 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	pwd(char **str, int *g_returns)
{
	char	path[PATH_MAX];

	(void)str;
	*g_returns = 0;
	if (getcwd(path, sizeof(path)) != NULL)
		printf("%s\n", path);
	else
	{
		printf("Erro ao obter o diretório\n");
		return ;
	}
}
