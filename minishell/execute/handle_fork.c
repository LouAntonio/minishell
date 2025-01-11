/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fork.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 18:19:58 by hmateque          #+#    #+#             */
/*   Updated: 2024/12/14 18:19:58 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	*is_fork(void)
{
	static int	fork_status;

	return (&fork_status);
}

void	open_fork(int *fork_id, int *fd, t_tree *root, char ***env_table)
{
	fork_id[0] = fork();
	if (fork_id[0] == -1)
		exit(EXIT_FAILURE);
	if (fork_id[0] == 0)
		execute_fork_right(fd[WRITE], fd[READ], root->left, env_table);
	close(fd[WRITE]);
	fork_id[1] = fork();
	if (fork_id[1] == -1)
		exit(EXIT_FAILURE);
	if (fork_id[1] == 0)
		execute_fork_left(fd[READ], fd[WRITE], root->right, env_table);
	close(fd[READ]);
}

void	execute_fork_right(int fd1, int fd2, t_tree *root, char ***env_table)
{
	int		status;
	char	*cwd;

	signal(SIGPIPE, sigpipe_handler);
	status = EXIT_SUCCESS;
	dup2(fd1, STDOUT_FILENO);
	close(fd1);
	close(fd2);
	status = execute_tree(root, env_table);
	free_mem(get_env_address());
	free_mem(get_mem_address());
	cwd = update_cwd(NULL);
	if (cwd)
	{
		free(cwd);
		cwd = NULL;
	}
	exit(status);
}

void	execute_fork_left(int fd1, int fd2, t_tree *root, char ***env_table)
{
	int		status;
	char	*cwd;

	status = EXIT_SUCCESS;
	dup2(fd1, STDIN_FILENO);
	close(fd1);
	close(fd2);
	status = execute_tree(root, env_table);
	free_mem(get_env_address());
	free_mem(get_mem_address());
	cwd = update_cwd(NULL);
	if (cwd)
	{
		free(cwd);
		cwd = NULL;
	}
	exit(status);
}
