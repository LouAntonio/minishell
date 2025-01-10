/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_aux_close_pipe.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 18:03:06 by hmateque          #+#    #+#             */
/*   Updated: 2025/01/10 18:34:15 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	handle_pipe_error(char *message)
{
	printf("minishell: parse error near '%s'\n", message);
	return (1);
}

char	*read_complete_command(void)
{
	char	*complete;

	complete = readline("> ");
	if (!complete)
	{
		printf("minishell: syntax error: unexpected end of file\n");
		exit(1);
	}
	while (complete[0] == '\0')
	{
		free(complete);
		complete = readline("> ");
		if (!complete)
		{
			printf("minishell: syntax error: unexpected end of file\n");
			exit(1);
		}
	}
	return (complete);
}

char	*join_command(char *command, char *complete)
{
	char	*temp;

	temp = ft_strjoin(command, " ");
	collect_mem(temp, MEM_CHAR_PTR, 0);
	command = temp;
	temp = ft_strjoin(command, complete);
	collect_mem(temp, MEM_CHAR_PTR, 0);
	command = temp;
	return (command);
}
