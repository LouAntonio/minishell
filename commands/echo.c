/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:52:12 by lantonio          #+#    #+#             */
/*   Updated: 2024/10/17 16:27:10 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	echo(char *str, int option)
{
	int	i;

	i = 4;
	if (!option)
		i = 7;
	printf("%s", str+(i + 1));
	if (!option)
		printf("\033[30m\033[47m%%\033[0m");
	printf("\n");
}
