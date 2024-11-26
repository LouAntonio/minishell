
int	dup_old_fd(int old_fd[2])
{
	old_fd[0] = dup(STDOUT_FILENO);
	if (old_fd[0] == -1)
		return (perror("dup error"), -1);
	old_fd[1] = dup(STDIN_FILENO);
	if (old_fd[1] == -1)
		return (perror("dup error"), close(old_fd[0]), -1);
	return (0);
}

int	handle_heredoc(Command *command_tree)
{
	int		heredoc_fd[2];
	int		status;
	pid_t	pid;
	char	*str;

	if (pipe(heredoc_fd) == -1)
		return (perror("Pipe error"), -1);
	pid = fork();
	if (pid == -1)
		return (perror("Fork error"), close(heredoc_fd[0]),
			close(heredoc_fd[1]), -1);
	if (pid == 0)
	{
		close(heredoc_fd[0]);
		while (1)
		{
			str = readline("> ");
			if (str == NULL)
				return (-1);
			if (strcmp(str, command_tree->heredoc_end) == 0)
			{
				free(str);
				break ;
			}
			write(heredoc_fd[1], str, strlen(str));
			write(heredoc_fd[1], "\n", 1);
			free(str);
		}
		close(heredoc_fd[1]);
		exit(EXIT_SUCCESS);
	}
	else
	{
		close(heredoc_fd[1]);
		if (dup2(heredoc_fd[0], STDIN_FILENO) == -1)
			return (perror("Dup2 error"), close(heredoc_fd[0]), -1);
		close(heredoc_fd[0]);
		waitpid(pid, &status, 0);
	}
	return (0);
}

int	handle_command_pipe(Command *command_tree, int *fd)
{
	int		status;
	pid_t	pid;

	if (pipe(fd) == -1)
		return (perror("Pipe error"), -1);
	pid = fork();
	if (pid == -1)
		return (perror("Fork error"), close(fd[0]), close(fd[1]), -1);
	if (pid == 0)
	{
		close(fd[0]);
		if (dup2(fd[1], STDOUT_FILENO) == -1)
		{
			perror("Dup2 error");
			exit(EXIT_FAILURE);
		}
		close(fd[1]);
		exit(EXIT_SUCCESS);
	}
	else
	{
		close(fd[1]);
		pid = fork();
		if (pid == -1)
			return (perror("Fork error"), close(fd[0]), -1);
		if (pid == 0)
		{
			if (dup2(fd[0], STDIN_FILENO) == -1)
			{
				perror("Dup2 error");
				exit(EXIT_FAILURE);
			}
			close(fd[0]);
			exit(EXIT_SUCCESS);
		}
		else
		{
			close(fd[0]);
			waitpid(pid, &status, 0);
		}
	}
	(void)command_tree;
	return (0);
}

int	execute_command(Command *command_tree, t_env **env,
	char **envp, int *g_returns)
{
	int	fd[2];

	if (command_tree->command)
	{
		if (command_tree->next != NULL)
		{
			if (handle_command_pipe(command_tree, fd) == -1)
				return (-1);
			if (!built_ins(command_tree, env, g_returns))
				path_commands(command_tree, env, envp, g_returns);
		}
		else
		{
			if (!built_ins(command_tree, env, g_returns))
				path_commands(command_tree, env, envp, g_returns);
		}
	}
	return (0);
}

int	reset_fds(int old_fd[2])
{
	if (dup2(old_fd[0], STDOUT_FILENO) == -1)
		return (perror("Dup2 error"), close(old_fd[0]), close(old_fd[1]), -1);
	close(old_fd[0]);
	if (dup2(old_fd[1], STDIN_FILENO) == -1)
		return (perror("Dup2 error"), close(old_fd[1]), -1);
	close(old_fd[1]);
	return (0);
}

int	run_commands(Command *command_tree, char **str,
	t_env **env, char **envp, int *g_returns)
{
	int	old_fd[2];
	int	status;
	int	fd_in;

	if (dup_old_fd(old_fd) == -1)
		return (-1);
	if (command_tree->heredoc && handle_heredoc(command_tree) == -1)
		return (close(old_fd[0]), close(old_fd[1]), -1);
	if (handle_redirection(command_tree) == -1)
		return (close(old_fd[0]), close(old_fd[1]), -1);
	if (check_red_in(command_tree, &fd_in) == -1)
		return (close(old_fd[0]), close(old_fd[1]), -1);
	if (execute_command(command_tree, env, envp, g_returns) == -1)
		return (close(old_fd[0]), close(old_fd[1]), -1);
	while (waitpid(-1, &status, WNOHANG) > 0)
		;
	if (reset_fds(old_fd) == -1)
		return (-1);
	(void)str;
	return (1);
}
