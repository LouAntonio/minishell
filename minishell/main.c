/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 18:22:51 by hmateque          #+#    #+#             */
/*   Updated: 2025/01/11 09:23:39 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

volatile int	g_signal;

static void	initialize_signals(void)
{
	g_signal = 0;
	if (signal(SIGINT, sigint_handler) == SIG_ERR || signal(SIGQUIT,
			SIG_IGN) == SIG_ERR || signal(SIGPIPE, SIG_IGN) == SIG_ERR)
		exit(EXIT_FAILURE);
}

static char	*init_read(void)
{
	static char	*input;
	char		*cwd;

	initialize_signals();
	input = readline("minishell: ");
	g_signal = 0;
	if (!input && g_signal == 0)
	{
		free_mem(get_env_address());
		free_mem(get_mem_address());
		cwd = update_cwd(NULL);
		cwd = update_cwd(NULL);
		if (cwd)
		{
			free(cwd);
			cwd = NULL;
		}
		exit(printf("exit\n"));
	}
	return (input);
}

static void	init_pwd(void)
{
	char	*cwd;

	cwd = get_pwd();
	update_cwd(cwd);
}

int	main(void)
{
	int						*fd;
	char					*input;
	static struct termios	term;
	t_tree					*root;
	char					**env_table;

	env_table = get_env_table();
	collect_env_mem(env_table);
	init_pwd();
	(void)term;
	//tcgetattr(STDIN_FILENO, &term);
	while (1)
	{
		fd = save_fd();
		root = NULL;
		input = init_read();
		if (!ft_strlen(input))
			continue ;
		add_history(input);
		parse(input, &root);
		execute(root, &env_table);
		reset_fd(fd);
		//tcsetattr(STDIN_FILENO, TCSANOW, &term);
		clean_tmp_files();
		free_mem(get_mem_address());
	}
}
