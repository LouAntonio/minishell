/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_execute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 18:22:00 by hmateque          #+#    #+#             */
/*   Updated: 2024/12/14 18:22:01 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	pre_execute(t_tree *root, char ***env_table)
{
	char	*str;
	t_node	*new_list;
	char	**words;
	int		status;

	status = EXIT_SUCCESS;
	preprocess_expansion(root->list);
	if (!root->list->value && !root->list->next)
		return (EXIT_SUCCESS);
	str = rejoin(root);
	words = remove_quotes(str, ' ');
	collect_words_mem(words);
	new_list = retokenizer(words);
	root->list = new_list;
	if (root->list)
	{
		status = execute_builtin(root, env_table);
		if (status == -1)
			status = execute_command(root);
	}
	return (status);
}

int	execute_builtin(t_tree *root, char ***env_table)
{
	char	*cmd;
	int		status;

	status = -1;
	cmd = root->list->value;
	if (!ft_strcmp(cmd, "cd"))
		status = cd(root->list, env_table);
	else if (!ft_strcmp(cmd, "echo"))
		status = echo(root->list);
	else if (!ft_strcmp(cmd, "pwd"))
		status = pwd();
	if (!ft_strcmp(cmd, "unset"))
		status = unset(root->list, env_table);
	else if (!ft_strcmp(cmd, "env"))
		status = env(root->list, *env_table);
	else if (!ft_strcmp(cmd, "export"))
		status = export(root->list, env_table);
	else if (!ft_strcmp(cmd, "exit"))
		status = exit_builtin(root->list);
	return (status);
}
