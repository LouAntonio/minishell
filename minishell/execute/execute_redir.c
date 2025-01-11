/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 18:18:58 by hmateque          #+#    #+#             */
/*   Updated: 2024/12/14 18:18:59 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	execute_redir_in(t_tree *root)
{
	int	fd;
	int	status;

	status = EXIT_SUCCESS;
	fd = open(root->right->list->value, O_RDONLY);
	if (fd < 0)
	{
		status = handle_error(root->right->list->value);
		return (status);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
		exit(EXIT_FAILURE);
	close(fd);
	return (EXIT_SUCCESS);
}

int	execute_redir_out_append(t_tree *root)
{
	int		fd;
	int		status;
	char	*infile;

	fd = -1;
	status = EXIT_SUCCESS;
	infile = root->right->list->value;
	if (root->list->type == OUT_REDIR)
		fd = open(infile, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	else if (root->list->type == APPEND)
		fd = open(infile, O_WRONLY | O_CREAT | O_APPEND, 0664);
	if (fd < 0)
	{
		status = handle_error(root->right->list->value);
		return (status);
	}
	if ((dup2(fd, STDOUT_FILENO)) == -1)
		exit(EXIT_FAILURE);
	close(fd);
	return (EXIT_SUCCESS);
}

int	check_file(t_tree *root)
{
	char	*str;
	t_node	*new_list;
	char	**words;

	preprocess_expansion(root->list);
	str = rejoin(root);
	if (!str)
	{
		ft_put_strjoin_fd("ambiguous redirect\n", NULL, 2);
		return (EXIT_FAILURE);
	}
	words = remove_quotes(str, ' ');
	collect_words_mem(words);
	new_list = retokenizer(words);
	if (new_list->next)
	{
		ft_put_strjoin_fd("ambiguous redirect\n", NULL, 2);
		return (EXIT_FAILURE);
	}
	root->list = new_list;
	return (EXIT_SUCCESS);
}

int	execute_redir(t_tree *root, char ***env_table)
{
	int	status;
	int	*fd_std;

	status = check_file(root->right);
	fd_std = save_fd();
	if (status)
		return (status);
	if (root->list->type != HEREDOC && (!root->right->list->value
			|| !ft_strcmp(root->right->list->value, "\"\"")
			|| !ft_strcmp(root->right->list->value, "''")
			|| !root->right->list->value[0]))
	{
		ft_put_strjoin_fd(" ", ": No such file or directory\n", 2);
		return (EXIT_FAILURE);
	}
	if (root->list->type == IN_REDIR || root->list->type == HEREDOC)
		status = execute_redir_in(root);
	else if (root->list->type == OUT_REDIR || root->list->type == APPEND)
		status = execute_redir_out_append(root);
	if (root->left && status == EXIT_SUCCESS)
		status = execute_tree(root->left, env_table);
	reset_fd(fd_std);
	return (status);
}

int	handle_error(char *message)
{
	perror(message);
	return (EXIT_FAILURE);
}
