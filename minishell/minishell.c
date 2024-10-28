/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 12:32:54 by lantonio          #+#    #+#             */
/*   Updated: 2024/10/28 12:00:34 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void signal_new_line(int signum)
{
	(void)signum;
	printf("\n");
	rl_replace_line("", 0);
    rl_on_new_line();
	rl_redisplay();
}


int	main(void)
{
	char	*command;
	
	configure_signal();
	while (1)
	{
		command = readline("minishell> ");
		if (check_signal_exit(command))
			break;
		identify_command(command);
		add_history(command);
		free(command);
	}
	free(command);
	rl_clear_history();
	return (0);
}
