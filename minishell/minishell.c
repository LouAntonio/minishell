/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 12:32:54 by lantonio          #+#    #+#             */
/*   Updated: 2024/10/30 10:58:12 by hmateque         ###   ########.fr       */
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


int	main(int ac, char **av, char **env)
{
	char	*command;
	t_env	*all_env;
	
	print_all_var(env);
	all_env = NULL;
	ft_set_value(ac, av, env, &all_env);
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
