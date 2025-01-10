/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_aux3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 22:09:12 by lantonio          #+#    #+#             */
/*   Updated: 2025/01/10 22:49:35 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	execute_heredoc_child(t_cmd *cmd, int hd_fd[2], t_env **env)
{
	char	*str2;

	close(hd_fd[0]);
	while (1)
	{
		str2 = readline("> ");
		if (str2 == NULL)
			exit(EXIT_FAILURE);
		if (strcmp(str2, cmd->heredoc_end) == 0)
		{
			free(str2);
			break ;
		}
		write(hd_fd[1], str2, ft_strlen(str2));
		write(hd_fd[1], "\n", 1);
		free(str2);
	}
	close(hd_fd[1]);
	free_env_list(env);
	free_all_mem();
	exit(0);
}

int	setup_heredoc_parent(int hd_fd[2], int old_fd[2], pid_t pid)
{
	int	status;

	close(hd_fd[1]);
	if (dup2(hd_fd[0], STDIN_FILENO) == -1)
		return (perror("Dup2 error"), close(hd_fd[0]),
			restore_original_fds(old_fd), -1);
	close(hd_fd[0]);
	waitpid(pid, &status, 0);
	return (1);
}
