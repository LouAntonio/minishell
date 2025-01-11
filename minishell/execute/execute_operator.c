/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_operator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 18:18:48 by hmateque          #+#    #+#             */
/*   Updated: 2024/12/14 18:18:49 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_status(t_tree *root, int status)
{
	if (status == 130)
		return (EXIT_FAILURE);
	if (root->list->type == AND && status != 0)
		return (EXIT_FAILURE);
	if (root->list->type == OR && status == 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	execute_and_or(t_tree *root, char ***env_table)
{
	int	status;

	status = EXIT_SUCCESS;
	status = execute_tree(root->left, env_table);
	if (!check_status(root, status))
		status = execute_tree(root->right, env_table);
	return (status);
}

int	execute_pipe(t_tree *root, char ***env_table)
{
	int	fork_id[2];
	int	fd[2];
	int	status;

	status = EXIT_SUCCESS;
	pipe(fd);
	open_fork(fork_id, fd, root, env_table);
	waitpid(fork_id[0], &status, 0);
	if (WEXITSTATUS(status) == 130)
	{
		waitpid(fork_id[1], &status, 0);
		return (130);
	}
	waitpid(fork_id[1], &status, 0);
	return (WEXITSTATUS(status));
}

t_node	*remove_parentheses(t_node *list)
{
	t_node	*head;
	t_node	*tmp;
	t_node	*last;

	tmp = list;
	while (tmp->next)
		tmp = tmp->next;
	head = list->next;
	list->next = NULL;
	head->prev = NULL;
	last = tmp->prev;
	last->next = NULL;
	tmp->prev = NULL;
	return (head);
}

int	execute_par(t_tree *root, char ***env_table)
{
	int		fork_id;
	int		status;
	t_tree	*mini_root;
	char	*cwd;

	status = EXIT_SUCCESS;
	mini_root = NULL;
	root->list = remove_parentheses(root->list);
	build_tree(&mini_root, root->list);
	fork_id = fork();
	if (fork_id == -1)
		exit(EXIT_FAILURE);
	if (fork_id == 0)
	{
		status = execute(mini_root, env_table);
		free_mem(get_env_address());
		free_mem(get_mem_address());
		cwd = update_cwd(NULL);
		if (cwd)
			free(cwd);
		exit(status);
	}
	waitpid(fork_id, &status, 0);
	return (WEXITSTATUS(status));
}
