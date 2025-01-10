/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_aux2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 22:08:29 by lantonio          #+#    #+#             */
/*   Updated: 2025/01/10 22:49:35 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	try_paths(char **paths, t_cmd *cmd, char **envp, int *g_returns)
{
	int		i;
	char	path[1024];

	i = 0;
	while (paths[i] != NULL)
	{
		build_path(paths[i], cmd->command, path, sizeof(path));
		if (access(path, X_OK) == 0)
			return (execute_command(path, cmd->args, envp, g_returns));
		i++;
	}
	return (printf("%s: command not found\n", cmd->command), -1);
}

void	build_path(const char *dir, const char *cmd, char *buffer, size_t size)
{
	ft_strlcpy(buffer, dir, size);
	ft_strlcat(buffer, "/", size);
	ft_strlcat(buffer, cmd, size);
}

int	execute_command(const char *path, char **args, char **envp, int *g_returns)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		return (perror("Fork error"), -1);
	if (pid == 0)
	{
		if (execve(path, args, envp) == -1)
			return (perror("Exec error"), -1);
		exit(EXIT_SUCCESS);
	}
	if (waitpid(pid, &status, 0) == -1)
		return (perror("Waitpid error"), -1);
	if (WIFEXITED(status))
		*g_returns = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		*g_returns = WTERMSIG(status);
	return (*g_returns);
}

int	save_original_fds(int old_fd[2])
{
	old_fd[0] = dup(STDOUT_FILENO);
	if (old_fd[0] == -1)
		return (perror("dup error"), -1);
	old_fd[1] = dup(STDIN_FILENO);
	if (old_fd[1] == -1)
		return (perror("dup error"), close(old_fd[0]), -1);
	return (1);
}

int	restore_original_fds(int old_fd[2])
{
	if (dup2(old_fd[0], STDOUT_FILENO) == -1)
		return (perror("Dup2 error"), close(old_fd[0]), close(old_fd[1]), -1);
	close(old_fd[0]);
	if (dup2(old_fd[1], STDIN_FILENO) == -1)
		return (perror("Dup2 error"), close(old_fd[1]), -1);
	close(old_fd[1]);
	return (1);
}
