/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 18:19:24 by hmateque          #+#    #+#             */
/*   Updated: 2024/12/14 18:19:24 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**find_paths(char *cmd)
{
	int		i;
	char	*path;
	char	**paths;

	path = getenv("PATH");
	if (cmd && (path == NULL || *path == '\0'))
		return (NULL);
	paths = ft_split(path, ':');
	i = 0;
	while (paths[i])
	{
		collect_mem(paths[i]);
		i++;
	}
	collect_mem(paths);
	return (paths);
}

char	*check_paths(char **paths, char *cmd)
{
	int		i;
	int		status;
	char	*path_name;
	char	*cmd_slash;

	i = 0;
	status = NOT_FOUND;
	if (!paths)
		return (cmd);
	cmd_slash = ft_strjoin("/", cmd);
	collect_mem(cmd_slash);
	while (paths[i] != NULL && status == NOT_FOUND)
	{
		path_name = ft_strjoin(paths[i], cmd_slash);
		collect_mem(path_name);
		status = check_bin_access(path_name);
		if (status == FOUND)
			break ;
		i++;
	}
	if (status != FOUND)
		error_status(status, cmd, FORK);
	return (path_name);
}

int	check_bin_access(char *path_name)
{
	struct stat	sb;

	if (stat(path_name, &sb) == 0)
	{
		if (S_ISDIR(sb.st_mode))
			return (IS_DIR);
	}
	if (access(path_name, F_OK) == 0)
	{
		if (access(path_name, X_OK) == 0)
			return (FOUND);
		else
			return (X_NOK);
	}
	else
		return (NOT_FOUND);
}

char	**list_to_array(t_node *head)
{
	char	**args;
	t_node	*tmp;
	int		i;
	int		count_ptr;

	count_ptr = 0;
	tmp = head;
	while (tmp)
	{
		count_ptr++;
		tmp = tmp->next;
	}
	args = allocate_mem(count_ptr + 1, sizeof(char *));
	i = 0;
	while (i < count_ptr)
	{
		args[i] = ft_strdup(head->value);
		collect_mem(args[i]);
		i++;
		head = head->next;
	}
	args[i] = NULL;
	return (args);
}
