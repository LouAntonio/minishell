/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 08:22:00 by lantonio          #+#    #+#             */
/*   Updated: 2024/11/07 08:33:44 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cd(char **str)
{
	int	vet_len;

	(void)str;
	vet_len = 1;
	if (vet_len == 1)
	{
		if (chdir(getenv("HOME")) != 0)
			perror("Erro ao mudar de diretório");
	}
	else
		if (chdir(str[1]) != 0)
			perror("Erro ao mudar de diretório");
}
