/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funts_aux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 11:56:22 by hmateque          #+#    #+#             */
/*   Updated: 2024/10/29 12:55:55 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	isset_in_mat(char **mat, char *str)
{
	int	i;

	i = -1;
	while (mat[++i])
		if (!ft_strcmp(mat[i], str))
			return (1);
	return (0);
}

int	check_read_from(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (!ft_strcmp(str[i], "<") || !ft_strcmp(str[i], "<<"))
			return (1);
	return (0);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = -1;
	while (s[++i])
		write(fd, &s[i], 1);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] && s2[i])
		i++;
	return ((int)((unsigned char)s1[i] - (unsigned char)s2[i]));
}

void	identify_command(char *command)
{
	char	**str;

	str = ft_split(command, ' ');
	if (str[0])
	{
		if (!ft_strcmp(str[0], "pwd"))
			pwd(str);
		else if (!ft_strcmp(str[0], "echo"))
			echo(str);
	}
}
