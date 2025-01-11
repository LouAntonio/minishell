/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 18:19:13 by hmateque          #+#    #+#             */
/*   Updated: 2024/12/14 18:19:14 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	execute(t_tree *root, char ***env_table)
{
	int	status;

	status = EXIT_SUCCESS;
	if (root == NULL)
		return (EXIT_FAILURE);
	signal(SIGINT, sigint_ign);
	status = execute_tree(root, env_table);
	if (update_exit_status(status) == 131)
		ft_putendl_fd("Quit (core dumped)", STDERR_FILENO);
	return (status);
}

int	execute_tree(t_tree *root, char ***env_table)
{
	if (root->list->type == AND || root->list->type == OR)
		return (execute_and_or(root, env_table));
	else if (root->list->type == PIPE)
		return (execute_pipe(root, env_table));
	else if (root->list->type == IN_REDIR || root->list->type == OUT_REDIR \
		|| root->list->type == APPEND || root->list->type == HEREDOC)
		return (execute_redir(root, env_table));
	else if (root->list->type == OPEN_PAR)
		return (execute_par(root, env_table));
	else
		return (pre_execute(root, env_table));
}

int	execute_command(t_tree *root)
{
	int	fork_id;
	int	status;

	status = EXIT_SUCCESS;
	fork_id = fork();
	if (fork_id == -1)
		exit(EXIT_FAILURE);
	else if (fork_id == 0)
		execute_child(status, root);
	waitpid(fork_id, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (status);
}

void	execute_child(int status, t_tree *root)
{
	char	*path_name;
	char	**paths;
	char	**args;

	signal(SIGQUIT, SIG_DFL);
	args = list_to_array(root->list);
	specific_errors(root->list->value);
	if (ft_strchr(root->list->value, '/'))
	{
		status = check_bin_access(root->list->value);
		if (status != FOUND)
			error_status(status, root->list->value, FORK);
		else
		{
			if (execve(root->list->value, args, __environ) == -1)
				error_status(EXEC_ERROR, root->list->value, FORK);
		}
	}
	else
	{
		paths = find_paths(root->list->value);
		path_name = check_paths(paths, root->list->value);
		if (execve(path_name, args, __environ) == -1)
			error_status(EXEC_ERROR, path_name, FORK);
	}
}
