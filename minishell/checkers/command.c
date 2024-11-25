/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 10:28:57 by hmateque          #+#    #+#             */
/*   Updated: 2024/11/25 14:07:41 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	print_command_tree(Command *root)
{
	int		i;
	Command	*current;

	current = root;
	return ;
	while (current != NULL)
	{
		printf("Comando: \033[0;32m%s\033[0m\n", current->command);
		printf("Argumentos:");
		i = -1;
		while (current->args[++i] != NULL)
			printf(" \033[0;34m%s\033[0m", current->args[i]);
		printf("\n");
		if (current->redirect_out != NULL)
			printf("Redirecionamento de saída: \033[0;33m%s\033[0m\n",
				current->redirect_out);
		if (current->redirect_in != NULL)
			printf("Redirecionamento de entrada: \033[0;33m%s\033[0m\n",
				current->redirect_in);
		if (current->next != NULL)
			printf("|\n|\nV\n");
		current = current->next;
	}
}

int	handle_redirection(Command *command_tree)
{
	int	fd;

	fd = dup(STDOUT_FILENO);
	if (command_tree->redirect_out != NULL)
	{
		if (command_tree->redirect_out_type == 1)
			fd = open(command_tree->redirect_out, O_WRONLY
					| O_CREAT | O_TRUNC, 0644);
		else
			fd = open(command_tree->redirect_out, O_WRONLY
					| O_CREAT | O_APPEND, 0644);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	return (fd);
}

int	check_red_in(Command *command_tree)
{
	if (command_tree->redirect_in != NULL)
		if (access(command_tree->redirect_in, R_OK) == -1)
			return (printf("minishell: %s: No such file or directory\n"
					, command_tree->redirect_in), 1);
	return (0);
}

int	built_ins(Command *command_tree, t_env **env, int *g_returns)
{
	if (!ft_strcmp(command_tree->command, "echo"))
		return (echo(command_tree->args, g_returns), 1);
	else if (!ft_strcmp(command_tree->command, "cd"))
		return (cd(command_tree->args, g_returns, env), 1);
	else if (!ft_strcmp(command_tree->command, "export"))
		return (ft_export(command_tree->args, env, g_returns), 1);
	else if (!ft_strcmp(command_tree->command, "env"))
		return (print_list(*env, 1), 1);
	else if (!ft_strcmp(command_tree->command, "pwd"))
		return (pwd(command_tree->args, g_returns), 1);
	else if (!ft_strcmp(command_tree->command, "unset"))
		return (ft_unset(command_tree->args, env, g_returns), 1);
	else if (!ft_strcmp(command_tree->command, "exit"))
		return (ft_exit(command_tree, env), 1);
	return (0);
}

int	path_commands(Command *command_tree, t_env **env, char **envp, int *g_returns)
{
	char		**paths;
	char		path[1024];
	int			i;
	pid_t		pid;
	int			status;
	int			cmd_ret;
	t_env		*env_copy;

	i = -1;
	env_copy = *env;
	if (access(command_tree->command, X_OK) == 0)
	{
		pid = fork();
			if (pid == -1)
				return (perror("Fork error"), -1);
			else if (pid == 0)
			{
				*g_returns = execve(command_tree->command, command_tree->args, envp);
				if (*g_returns == -1)
					return (perror("Exec error"), -1);
			}
			else
			{
				if (waitpid(pid, &status, 0) == -1)
					return (perror("Waitpid error"), -1);
				if (WIFEXITED(status))
					cmd_ret = WEXITSTATUS(status);
				else if (WIFSIGNALED(status))
					cmd_ret = WTERMSIG(status);
				return (cmd_ret);
			}
	}
	while (env_copy != NULL)
	{
		if (!ft_strcmp(env_copy->name, "PATH"))
			break ;
		env_copy = env_copy->next;
	}
	if (env_copy == NULL)
		return (printf("Command not found\n"), -1);
	paths = ft_split(env_copy->value, ':');
	while (paths[++i] != NULL)
	{
		ft_strlcpy(path, paths[i], sizeof(path));
		ft_strlcat(path, "/", sizeof(path));
		ft_strlcat(path, command_tree->command, sizeof(path));
		if (access(path, X_OK) == 0)
		{
			pid = fork();
			if (pid == -1)
				return (perror("Fork error"), -1);
			else if (pid == 0)
			{
				*g_returns = execve(path, command_tree->args, envp);
				if (*g_returns == -1)
					return (perror("Exec error"), -1);
			}
			else
			{
				if (waitpid(pid, &status, 0) == -1)
					return (perror("Waitpid error"), -1);
				if (WIFEXITED(status))
					cmd_ret = WEXITSTATUS(status);
				else if (WIFSIGNALED(status))
					cmd_ret = WTERMSIG(status);
				return (cmd_ret);
			}
		}
	}
	*g_returns = 127;
	return (printf("%s: command not found\n", command_tree->command), -1);
}

int	run_commands(Command *command_tree, char **str, t_env **env, char **envp, int *g_returns)
{
	int		fd[2];
	int		old_fd_out;
	int		old_fd_in;
	pid_t	pid;
	int		status;
	int		fd_in;

	// Salvar o descritor de arquivo original do stdout
	old_fd_out = dup(STDOUT_FILENO);
	if (old_fd_out == -1)
		return (perror("dup error"), -1);
	// Salvar o descritor de arquivo original do stdin
	old_fd_in = dup(STDIN_FILENO);
	if (old_fd_in == -1)
		return (perror("dup error"), close(old_fd_out), -1);
	// Heredoc
	if (command_tree->heredoc)
	{
		int heredoc_fd[2];
		if (pipe(heredoc_fd) == -1)
			return (perror("Pipe error"), close(old_fd_in), close(old_fd_out), -1);
		pid = fork();
		if (pid == -1)
			return (perror("Fork error"), close(heredoc_fd[0])
				, close(heredoc_fd[1]), close(old_fd_out), close(old_fd_in), -1);
		if (pid == 0) {
			close(heredoc_fd[0]);
			char *str;
			while (1)
			{
				str = readline("> ");
				if (str == NULL)
					return (-1);
				if (strcmp(str, command_tree->heredoc_end) == 0) {
					free(str);
					break;
				}
				//printf("%s\n", str);
				write(heredoc_fd[1], str, ft_strlen(str));
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
				return (perror("Dup2 error"), close(heredoc_fd[0])
					, close(old_fd_out), close(old_fd_in), -1);
			close(heredoc_fd[0]);
			waitpid(pid, &status, 0);
		}
	}
	// redirecionamento de output
	fd[1] = handle_redirection(command_tree);
	if (fd[1] == -1) 
		return (close(old_fd_out), close(old_fd_in), -1);
	if (check_red_in(command_tree))
		return (close(old_fd_out), close(old_fd_in), -1);
	if (command_tree->redirect_in != NULL)
	{
		fd_in = open(command_tree->redirect_in, O_RDONLY);
		if (fd_in == -1)
			return (perror("Open input file error")
				, close(old_fd_out), close(old_fd_in), -1);
		if (dup2(fd_in, STDIN_FILENO) == -1)
			return (perror("Dup2 error"), close(fd_in)
				, close(old_fd_out), close(old_fd_in), -1);
		close(fd_in);
	}

	// execucao do comando
	if (command_tree->command)
	{
		if (command_tree->next != NULL) {
			if (pipe(fd) == -1)
				return (perror("Pipe error"), close(old_fd_out), close(old_fd_in), -1);
			pid = fork();
			if (pid == -1)
				return (close(fd[0]), close(fd[1]), perror("Fork error")
					, close(old_fd_out), close(old_fd_in), -1);
			if (pid == 0)
			{
				close(fd[0]);
				if (dup2(fd[1], STDOUT_FILENO) == -1) {
					perror("Dup2 error");
					exit(EXIT_FAILURE);
				}
				close(fd[1]);
				if (!built_ins(command_tree, env, g_returns))
					path_commands(command_tree, env, envp, g_returns);
				exit(EXIT_SUCCESS);
			} else {
				close(fd[1]);
				pid = fork();
				if (pid == -1)
					return (close(fd[0]), perror("Fork error")
						, close(old_fd_out), close(old_fd_in), -1);
				if (pid == 0)
				{
					if (dup2(fd[0], STDIN_FILENO) == -1) {
						perror("Dup2 error");
						exit(EXIT_FAILURE);
					}
					close(fd[0]);
					if (command_tree->next != NULL)
						run_commands(command_tree->next, str, env, envp, g_returns);
					exit(EXIT_SUCCESS);
				}
				else
				{
					close(fd[0]);
					waitpid(pid, &status, 0);
					waitpid(pid, &status, 0);
				}
			}
		}
		else
		{
			if (!built_ins(command_tree, env, g_returns))
				path_commands(command_tree, env, envp, g_returns);
		}
	}
	if (dup2(old_fd_out, STDOUT_FILENO) == -1)
		return (perror("Dup2 error"), close(old_fd_out), close(old_fd_in), -1);
	close(old_fd_out);
	if (dup2(old_fd_in, STDIN_FILENO) == -1)
		return (perror("Dup2 error"), close(old_fd_in), -1);
	close(old_fd_in);
	return (1);
}

char	*close_pipe(char *command)
{
	int		i;
	char	*complete;

	i = 0;
	complete = NULL;
	while (command[i])
		i++;
	if (command[--i] == '|')
	{
		complete = readline("pipe> ");
		while (!complete || complete[0] == '\0')
		{
			free(complete);
			complete = readline("pipe> ");
		}
	}
	else
		return (command);
	command = ft_strjoin(command, " ");
	command = ft_strjoin(command, complete);
	free(complete);
	return (command);
}

char	**expander(char **str, t_env **env, int *g_returns)
{
	int		i;
	t_env	*cur;

	i = -1;
	cur = *env;
	while (str[++i])
	{
		if (!ft_strcmp("$?", str[i]))
			str[i] = ft_strdup(ft_itoa(*g_returns));
		else
		{
			cur = *env;
			while (cur)
			{
				if (!ft_strcmp(cur->name, str[i]+1))
				{
					str[i] = ft_strdup(cur->value);
					break ;
				}
				cur = cur->next;
			}
		}
	}
	return (str);
}

void	create_files(char **str)
{
	int	i;
	int	fd;

	i = -1;
	while (str[++i])
	{
		if (!ft_strcmp(str[i], ">>"))
		{
			if (str[i + 1])
			{
				fd = open(str[++i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
				if (fd != -1)
					close(fd);
			}
		}
		else if (!ft_strcmp(str[i], ">"))
		{
			if (str[i + 1])
			{
				fd = open(str[++i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
				if (fd != -1)
					close(fd);
			}
		}
	}
}

void	identify_command(char *command, t_env **env, char **envp, int *g_returns)
{
	Token	**classified_tokens;
	char	**str;
	Command	*command_tree;

	str = NULL;
	command = close_pipe(command);
	command = trim_spaces(command);
	if (!command)
		return ;
	str = tokenize(command);
	str = expander(str, env, g_returns);
	free(command);
	classified_tokens = classify_tokens(str);
	command_tree = build_command_tree(classified_tokens);
	create_files(str);
	print_command_tree(command_tree);
	if (command_tree)
		run_commands(command_tree, str, env, envp, g_returns);
	free_matrix(str);
}
