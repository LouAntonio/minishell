/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 12:32:54 by lantonio          #+#    #+#             */
/*   Updated: 2024/11/14 15:33:51 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void	signal_new_line(int signum)
{
	
	(void)signum;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	signal_new_line_2(int signum)
{
	(void)signum;
	printf("\n");
}

int	main(int ac, char **av, char **env)
{
	char	*command;
	t_env	*all_env;

	all_env = NULL;
	ft_set_value(ac, av, env, &all_env);
	configure_signal();
	while (1)
	{
		signal(SIGINT, signal_new_line);
		command = readline("minishell$ ");
		if (command != NULL)
		{
			identify_command(command, &all_env, env);
			add_history(command);
			free(command);
		}
		else
			break ;
		signal(SIGINT, signal_new_line_2);
	}
	free(command);
	rl_clear_history();
	return (0);
}
