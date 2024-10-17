/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 12:32:54 by lantonio          #+#    #+#             */
/*   Updated: 2024/10/17 16:31:27 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int	g_work;

void	identify_command(char *command)
{
	if (!strcmp("pwd", command))
		pwd();
	else if (!strncmp(command, "echo -n", 7))
		echo(command, 0);
	else if (!strncmp(command, "echo", 4))
		echo(command, 1);
}

int	main(void)
{
	char	*command;
	while (!g_work)
	{
		command = readline("$> ");
		identify_command(command);
		add_history(command);
	}
	return (0);
}
