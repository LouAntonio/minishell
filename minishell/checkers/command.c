/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 10:28:57 by hmateque          #+#    #+#             */
/*   Updated: 2024/10/30 10:29:25 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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