/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 18:03:06 by hmateque          #+#    #+#             */
/*   Updated: 2025/01/10 18:35:10 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*handle_child_process(int pipefd[2])
{
	char	*complete;

	signal(SIGINT, handle_sigint_child);
	complete = read_complete_command();
	write(pipefd[1], complete, strlen(complete));
	close(pipefd[0]);
	close(pipefd[1]);
	exit(0);
}

static char	*handle_parent_process(int pipefd[2], char *command)
{
	char	buffer[1024];
	int		nbytes;
	char	*complete;

	close(pipefd[1]);
	wait(NULL);
	nbytes = read(pipefd[0], buffer, sizeof(buffer));
	if (nbytes == -1)
	{
		perror("Read failed");
		close(pipefd[0]);
		return (NULL);
	}
	buffer[nbytes] = '\0';
	complete = strdup(buffer);
	close(pipefd[0]);
	command = join_command(command, complete);
	free(complete);
	return (command);
}

char	*close_pipe(char *command, int i, int j)
{
	int		pipefd[2];
	pid_t	pid;

	i = ft_strlen(command);
	if (command[0] == '|')
		return (handle_pipe_error("|"), NULL);
	j = i - 2;
	if (command[--i] == '|')
	{
		while (command[j] == ' ' || command[j] <= 13)
			j--;
		if (command[j] == '|')
			return (handle_pipe_error("|"), NULL);
		if (pipe(pipefd) == -1)
			return (perror("Pipe failed"), NULL);
		pid = fork();
		if (pid == -1)
		{
			close(pipefd[0]);
			close(pipefd[1]);
			return (perror("Fork failed"), NULL);
		}
		if (pid == 0)
			handle_child_process(pipefd);
		else
			return (handle_parent_process(pipefd, command));
	}
	return (command);
}
