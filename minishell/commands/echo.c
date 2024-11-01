/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:52:12 by lantonio          #+#    #+#             */
/*   Updated: 2024/11/01 09:24:04 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	echo(char **str, t_env *env)
{
	int	i;
	int	fd;
	int	vet_len;

	i = 0;
	fd = 1;
	vet_len = 0;
	while (str[vet_len])
		vet_len++;
	if (vet_len >= 2)
	{
		if (!ft_strcmp(str[vet_len - 2], ">"))
			fd = open(str[vet_len - 1], O_WRONLY | O_CREAT | O_TRUNC,
					S_IRUSR | S_IWUSR);
		else if (!ft_strcmp(str[vet_len - 2], ">>"))
			fd = open(str[vet_len - 1], O_WRONLY | O_CREAT | O_APPEND,
					S_IRUSR | S_IWUSR);
		if (!ft_strcmp(str[1], "-n"))
			i = 1;
	}
	if (!check_read_from(str))
	{
		while (str[++i])
		{
			if (check_cipher(str[i], fd, env))
				;
			else if (!(!ft_strcmp(str[i], ">") || !ft_strcmp(str[i], ">>")
					|| !ft_strcmp(str[i - 1], ">") || !ft_strcmp(str[i - 1],
						">>")))
				ft_putstr_fd(str[i], fd);
			if (str[i + 1])
				ft_putstr_fd(" ", fd);
		}
		if (str[1])
			if (!ft_strcmp(str[1], "-n"))
				ft_putstr_fd("\033[30m\033[47m%\033[0m", fd);
	}
	ft_putstr_fd("\n", fd);
	if (fd != 1)
		close(fd);
}
