/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:10:13 by lantonio          #+#    #+#             */
/*   Updated: 2024/10/31 08:13:19 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	write_path_on_fd(int fd)
{
	char	path[PATH_MAX];

	if (getcwd(path, sizeof(path)) != NULL)
		ft_putstr_fd(path, fd);
	else
		perror("Erro ao obter o diretório");
}

void	pwd(char **str)
{
	int		i;
	int		fd;
	int		vet_len;

	i = 0;
	fd = 1;
	vet_len = 0;
	while (str[vet_len])
		vet_len++;
	if (vet_len > 1)
	{
		while (str[++i])
		{
			if (ft_strcmp(str[1], ">") != 0 && ft_strcmp(str[1], ">>") != 0 && ft_strcmp(str[1], "<") != 0)
			{
				printf("pwd: too many arguments\n");
				break ;
			}
			if (!ft_strcmp(str[i], ">"))
				fd = open(str[i + 1], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
			else if (!ft_strcmp(str[i], ">>"))
				fd = open(str[i + 1], O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
			write_path_on_fd(fd);
			ft_putstr_fd("\n", fd);
			if  (fd != 1)
				close(fd);
		}
	}
	else
		write_path_on_fd(fd);
	ft_putstr_fd("\n", fd);
	if (vet_len > 3 && 0)
		printf("pwd: too many arguments\n");
}
