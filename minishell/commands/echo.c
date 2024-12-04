/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:52:12 by lantonio          #+#    #+#             */
/*   Updated: 2024/12/04 10:53:30 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int matrix_len(char **matrix)
{
    int len = 0;

    if (!matrix)
        return (0);
    while (matrix[len])
        len++;
    return (len);
}


void	echo(char **str, int *g_returns)
{
	int	i;
	int	fd;

	i = 1;
	fd = dup(STDOUT_FILENO);
	if (matrix_len(str) == 1)
	{
		ft_putstr_fd("\n", fd);
		return ;
	}
	if (!ft_strcmp(str[1], "-n"))
		i = 2;
	while (str[i])
	{
		ft_putstr_fd(str[i], fd);
		if (str[i + 1])
			ft_putstr_fd(" ", fd);
		i++;
	}
	if (!ft_strcmp(str[1], "-n"))
		ft_putstr_fd("\033[30m\033[47m%\033[0m", fd);
	ft_putstr_fd("\n", fd);
	*g_returns = 0;
}
