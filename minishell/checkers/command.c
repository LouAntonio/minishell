/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 10:28:57 by hmateque          #+#    #+#             */
/*   Updated: 2024/11/13 18:53:32 by hmateque         ###   ########.fr       */
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

int	built_ins(Command *command_tree, char **str, t_env **env)
{
	int	ret;

	ret = 0;
	if (!ft_strcmp(command_tree->command, "echo"))
	{
		ret = 1;
		echo(command_tree->args, *env);
	}
	else if (!ft_strcmp(command_tree->command, "cd"))
	{
		ret = 1;
		cd(command_tree->args);
	}
	else if (!ft_strcmp(command_tree->command, "export"))
	{
		ret = 1;
		ft_export(command_tree->args, env);
	}
	else if (!ft_strcmp(command_tree->command, "pwd"))
	{
		ret = 1;
		pwd(command_tree->args);
	}
	else if (!ft_strcmp(command_tree->command, "unset"))
	{
		ret = 1;
		ft_unset(command_tree->args, env);
	}
	(void)str;
	return (ret);
}

int	path_commands(Command *command_tree, t_env **env, char **envp)
{
	char		**paths;
	char		path[1024];
	int			i;
	pid_t		pid;
	int			status;
	int			cmd_ret;

	i = -1;
	while (env != NULL)
	{
		if (!ft_strcmp((*env)->name, "PATH"))
			break ;
		*env = (*env)->next;
	}
	paths = ft_split((*env)->value, ':');
	while (paths[++i] != NULL)
	{
		ft_strlcpy(path, paths[i], sizeof(path));// Copia paths[i] para path.
		ft_strlcat(path, "/", sizeof(path));// Adiciona a barra.
		ft_strlcat(path, command_tree->command, sizeof(path));// Adiciona o comando.
		if (access(path, X_OK) == 0)
		{
			pid = fork();
			if (pid == -1)
				return (perror("Fork error"), -1);
			else if (pid == 0)
			{
				if (execve(path, command_tree->args, envp) == -1)
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
	return (printf("Command not found!\n"), -1);
}

int	run_commands(Command *command_tree, char **str, t_env **env, char **envp)
{
	int		fd[2];
	int		old_fd;
	pid_t	pid;
	int		status;

	old_fd = dup(STDOUT_FILENO);
	fd[1] = handle_redirection(command_tree);
	if (command_tree->command == NULL)
		return (printf("KO\n"), -1);
	if (command_tree->next != NULL)
	{
		if (pipe(fd) == -1)
			return (perror("Pipe error"), -1);
		pid = fork();
		if (pid == -1)
			return (close(fd[0]), close(fd[1]), perror("Fork error"), -1);
		if (pid == 0)
		{
			close(fd[0]);
			if (dup2(fd[1], STDOUT_FILENO) == -1)
				return (perror("Dup2 error"), -1);
			close(fd[1]);
			if (!built_ins(command_tree, str, env))
				path_commands(command_tree, env, envp);
			exit(EXIT_SUCCESS);
		}
		else
		{
			close(fd[1]);
			pid = fork();
			if (pid == -1)
				return (close(fd[0]), perror("Fork error"), -1);
			if (pid == 0)
			{
				if (dup2(fd[0], STDIN_FILENO) == -1)
					return (close(fd[0]), perror("Dup2 error"), -1);
				close(fd[0]);
				if (command_tree->next != NULL)
					run_commands(command_tree->next, str, env, envp);
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
		if (!built_ins(command_tree, str, env))
			path_commands(command_tree, env, envp);
	if (dup2(old_fd, STDOUT_FILENO) == -1)
		return (perror("Dup2 error"), -1);
	close(old_fd);
	return (1);
}

void	identify_command(char *command, t_env **env, char **envp)
{
	int		i;
	Token	**classified_tokens;
	char	**str;
	Command	*command_tree;

	i = 0;
	str = NULL;
	while (command[i])
    {
        if (!ft_isspace(command[i]))
            break;
        i++;
    }
    if (command[i] == '\0')
		return ;
	str = tokenize(command);
	//str = tokenizar(command, ' ');
	classified_tokens = classify_tokens(str);
	command_tree = build_command_tree(classified_tokens);
	//while (classified_tokens[++i] != NULL)
	//	printf("Token: \033[0;32m%s\033[0m, Tipo: \033[0;31m%d\033[0m\n",
	//		classified_tokens[i]->value, classified_tokens[i]->type);
	//if (validate_command_tree(command_tree))
	//	printf("Comando válido e pronto para execução.\n");
	//else
	//	printf("Comando inválido.\n");
	print_command_tree(command_tree);
	run_commands(command_tree, str, env, envp);
	(void)env;
}
