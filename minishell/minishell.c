/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 12:32:54 by lantonio          #+#    #+#             */
/*   Updated: 2024/12/14 23:54:31 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int g_return ;

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

static char	*int_read(t_env **env)
{
	char	*input;

	configure_signal();
	input = readline("minishell$ ");
	if (!input)
	{
		// Liberar all_env;
		free_env_list(env);
		ft_putstr_fd("exit\n", 1);
		exit(0);
	}
	return (input);
}

int	main(int ac, char **av, char **env)
{
	char	*command;
	t_env	*all_env;

	all_env = NULL;
	ft_set_value(ac, av, env, &all_env);
	while (1)
	{
		command = int_read(&all_env);
		if (!ft_strlen(command))
			continue ;
		add_history(command);
		signal(SIGINT, signal_new_line_2);
		identify_command(command, &all_env, env, &g_return);
		signal(SIGINT, signal_new_line);
	}
	rl_clear_history();
	return (0);
}
