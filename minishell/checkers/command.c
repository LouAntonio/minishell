/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 10:28:57 by hmateque          #+#    #+#             */
/*   Updated: 2025/01/10 22:49:35 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	handle_heredoc(t_cmd *cmd, int old_fd[2], t_env **env)
{
	int		hd_fd[2];
	pid_t	pid;

	if (pipe(hd_fd) == -1)
		return (perror("Pipe error"), restore_original_fds(old_fd), -1);
	pid = fork();
	if (pid == -1)
		return (perror("Fork error"), close(hd_fd[0]), close(hd_fd[1]), -1);
	if (pid == 0)
		execute_heredoc_child(cmd, hd_fd, env);
	return (setup_heredoc_parent(hd_fd, old_fd, pid));
}

int	handle_pipe_execution(t_cmd *cmd,
	int fd[2], t_env **env, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (close(fd[0]), close(fd[1]), perror("Fork error"), -1);
	if (pid == 0)
	{
		close(fd[0]);
		if (dup2(fd[1], STDOUT_FILENO) == -1)
		{
			perror("Dup2 error");
			exit(EXIT_FAILURE);
		}
		close(fd[1]);
		if (!built_ins(cmd, env, &g_return))
			path_commands(cmd, env, envp, &g_return);
		free_env_list(env);
		free_all_mem();
		exit(EXIT_SUCCESS);
	}
	close(fd[1]);
	return (pid);
}

int	handle_pipe(t_cmd *cmd, int old_fd[2], t_env **env, char **envp)
{
	int		fd[2];
	pid_t	pid;
	int		status;

	if (pipe(fd) == -1)
		return (perror("Pipe error"), restore_original_fds(old_fd), -1);
	pid = handle_pipe_execution(cmd, fd, env, envp);
	if (pid == -1)
		return (-1);
	if (fork() == 0)
	{
		if (dup2(fd[0], STDIN_FILENO) == -1)
			(perror("Dup2 error"), exit(EXIT_FAILURE));
		close(fd[0]);
		run_commands(cmd->next, env, envp);
		free_env_list(env);
		free_all_mem();
		exit(EXIT_SUCCESS);
	}
	close(fd[0]);
	waitpid(pid, &status, 0);
	return (1);
}

int	run_commands(t_cmd *cmd, t_env **env, char **envp)
{
	int		old_fd[2];
	int		fd_in;
	int		fd_out;

	if (save_original_fds(old_fd) == -1)
		return (-1);
	if (cmd->heredoc && handle_heredoc(cmd, old_fd, env) == -1)
		return (-1);
	fd_out = handle_redirection(cmd);
	if (fd_out == -1 || check_red_in(cmd, &fd_in))
		return (restore_original_fds(old_fd), -1);
	if (cmd->command)
	{
		if (cmd->next != NULL)
		{
			if (handle_pipe(cmd, old_fd, env, envp) == -1)
				return (-1);
		}
		else if (!built_ins(cmd, env, &g_return))
			path_commands(cmd, env, envp, &g_return);
	}
	while (waitpid(-1, NULL, WNOHANG) > 0)
		;
	return (restore_original_fds(old_fd));
}
