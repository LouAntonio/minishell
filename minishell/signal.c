/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 18:23:06 by hmateque          #+#    #+#             */
/*   Updated: 2024/12/14 18:23:07 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

void	sigint_ign(int signo)
{
	(void)signo;
	g_signal = 130;
	ft_putstr_fd("\n", 1);
	update_exit_status(130);
}

void	sigint_handler(int signo)
{
	(void)signo;
	rl_on_new_line();
	rl_replace_line("", 0);
	ft_putstr_fd("\n", 1);
	rl_redisplay();
	g_signal = 130;
	update_exit_status(130);
}

void	sigint_cmd_handler(int signo)
{
	(void)signo;
	write(STDOUT_FILENO, "\n", 1);
	close(STDIN_FILENO);
	g_signal = 130;
	update_exit_status(130);
}

void	sigpipe_handler(int signo)
{
	char	*cwd;

	(void)signo;
	g_signal = 13;
	update_exit_status(13);
	free_mem(get_mem_address());
	free_mem(get_env_address());
	cwd = update_cwd(NULL);
	if (cwd)
	{
		free(cwd);
		cwd = NULL;
	}
	exit(13);
}
