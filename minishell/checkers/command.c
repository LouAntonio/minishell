/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 10:28:57 by hmateque          #+#    #+#             */
/*   Updated: 2024/10/30 16:17:21 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	identify_command(char *command, t_env **env)
{
	char	**str;

	str = ft_split(command, ' ');
	if (str[0])
	{
		if (!ft_strcmp(str[0], "pwd"))
			pwd(str);
		else if (!ft_strcmp(str[0], "echo"))
			echo(str, *env);
		else if (!ft_strcmp(str[0], "env"))
			print_list(*env);
	}
}

int	check_cipher(char *str, int fd, t_env *env)
{
	int		i;
	char	*result;
	char	*new_str;

	i = 0;
	result = ft_strchr(str, '$');
	if (result == NULL)
		return (0);
	result++;
	while (result[i] != '\0')
		i++;
	new_str = (char *)malloc(sizeof(char) * (i + 1));
	i = 0;
	while (result[i] != '\0')
	{
		new_str[i] = result[i];
		i++;
	}
	new_str[i] = '\0';
	search_and_print_list(env, new_str, fd);
	free(new_str);
	return (1);
}
