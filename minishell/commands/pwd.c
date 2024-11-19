/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:10:13 by lantonio          #+#    #+#             */
/*   Updated: 2024/11/18 18:21:51 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	pwd(char **str)
{
	int		vet_len;
	char	path[PATH_MAX];

	vet_len = 0;
	while (str[vet_len])
		vet_len++;
	if (vet_len > 0)
	{
		printf("KO\n");
		return ;
	}
	if (getcwd(path, sizeof(path)) != NULL)
		printf("%s\n", path);
	else
		printf("Erro ao obter o diretório\n");
}
