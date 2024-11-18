/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:52:12 by lantonio          #+#    #+#             */
/*   Updated: 2024/11/15 15:54:57 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	echo(char **str, t_env *env)
{
	int	i;
	int	fd;

	i = 1;
	fd = STDOUT_FILENO;
	if (!str[0])
	{
		ft_putstr_fd("\n", fd);
		return ;
	}
	if (!ft_strcmp(str[1], "-n"))
		i = 2;
	while (str[i])
	{
		if (check_cipher(str[i], fd, env))
			;
		else
			ft_putstr_fd(str[i], fd);
		if (str[i + 1])
			ft_putstr_fd(" ", fd);
		i++;
	}
	if (!ft_strcmp(str[1], "-n"))
		ft_putstr_fd("\033[30m\033[47m%\033[0m", fd);
	ft_putstr_fd("\n", fd);
}
