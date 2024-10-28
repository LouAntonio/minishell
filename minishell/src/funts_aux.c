/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funts_aux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 11:56:22 by hmateque          #+#    #+#             */
/*   Updated: 2024/10/28 12:00:41 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	identify_command(char *command)
{
	if (!strcmp("pwd", command))
		pwd();
	else if (!strncmp(command, "echo -n", 7))
		echo(command, 0);
	else if (!strncmp(command, "echo", 4))
		echo(command, 1);
}
