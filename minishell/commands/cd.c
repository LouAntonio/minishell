/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 08:22:00 by lantonio          #+#    #+#             */
/*   Updated: 2024/11/18 17:54:32 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cd(char **str)
{
	int	vet_len;

	vet_len = 0;
	while (str[vet_len])
		vet_len++;
	if (vet_len == 0)
	{
		if (chdir(getenv("HOME")) != 0)
			perror("Erro ao mudar de diretório");
	}
	else if (vet_len == 2)
	{
		if (chdir(str[1]) != 0)
			perror("Erro ao mudar de diretório");
	}
	else
		printf("minishell: cd: too many arguments\n");
}
