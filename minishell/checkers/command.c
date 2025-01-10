/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 10:28:57 by hmateque          #+#    #+#             */
/*   Updated: 2025/01/10 21:48:07 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	path_commands(Command *cmd, t_env **env, char **envp, int *g_returns)
{
	char	**paths;
	int		result;

	paths = get_env_paths(*env);
	if (!validate_env(env))
		return (printf("Env Error\n"), -1);
	if (is_absolute_path(cmd->command))
		return (execute_absolute_path(cmd, envp, g_returns));
	if (!paths)
		return (printf("Command not found\n"), -1);
	result = try_paths(paths, cmd, envp, g_returns);
	free_matrix(paths);
	if (result == -1)
		*g_returns = 127;
	return (result);
}

bool	validate_env(t_env **env)
{
	return (*env != NULL);
}

bool	is_absolute_path(const char *command)
{
	return (command[0] == '/');
}

int	execute_absolute_path(Command *cmd, char **envp, int *g_returns)
{
	if (access(cmd->command, X_OK) == 0)
		return (execute_command(cmd->command, cmd->args, envp, g_returns));
	return (printf("minishell: %s: No such file or directory\n",
			cmd->command), -1);
}

char	**get_env_paths(t_env *env)
{
	while (env)
	{
		if (!ft_strcmp(env->name, "PATH"))
		{
			if (env->value && *env->value)
				return (ft_split(env->value, ':'));
			return (NULL);
		}
		env = env->next;
	}
	return (NULL);
}

int	try_paths(char **paths, Command *cmd, char **envp, int *g_returns)
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

static int	save_original_fds(int old_fd[2])
{
	old_fd[0] = dup(STDOUT_FILENO);
	if (old_fd[0] == -1)
		return (perror("dup error"), -1);
	old_fd[1] = dup(STDIN_FILENO);
	if (old_fd[1] == -1)
		return (perror("dup error"), close(old_fd[0]), -1);
	return (1);
}

static int	restore_original_fds(int old_fd[2])
{
	if (dup2(old_fd[0], STDOUT_FILENO) == -1)
		return (perror("Dup2 error"), close(old_fd[0]), close(old_fd[1]), -1);
	close(old_fd[0]);
	if (dup2(old_fd[1], STDIN_FILENO) == -1)
		return (perror("Dup2 error"), close(old_fd[1]), -1);
	close(old_fd[1]);
	return (1);
}

static int	execute_heredoc_child(Command *cmd, int hd_fd[2], t_env **env)
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

static int	setup_heredoc_parent(int hd_fd[2], int old_fd[2], pid_t pid)
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

static int	handle_heredoc(Command *cmd, int old_fd[2], t_env **env)
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

static int	handle_pipe_execution(Command *cmd,
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

static int	handle_pipe(Command *cmd, int old_fd[2], t_env **env, char **envp)
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

int	run_commands(Command *cmd, t_env **env, char **envp)
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
