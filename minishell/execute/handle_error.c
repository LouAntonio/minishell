/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 18:19:32 by hmateque          #+#    #+#             */
/*   Updated: 2024/12/14 18:19:33 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_file_status(int status, char *cmd, struct stat sb)
{
	if (S_ISDIR(sb.st_mode) && ft_strchr(cmd, '/'))
	{
		ft_put_strjoin_fd(cmd, ": Is a directory\n", 2);
		status = 126;
	}
	else if (S_ISDIR(sb.st_mode))
	{
		ft_put_strjoin_fd(cmd, ": command not found\n", 2);
		status = 127;
	}
	return (status);
}

void	specific_errors(char *cmd)
{
	int	status;

	status = EXIT_SUCCESS;
	if (ft_strcmp(".", cmd) == 0)
	{
		ft_put_strjoin_fd(cmd, ": filename argument required\n", 2);
		status = 2;
	}
	else if (ft_strcmp("..", cmd) == 0 || ft_strcmp("", cmd) == 0)
	{
		ft_put_strjoin_fd(cmd, ": command not found\n", 2);
		status = 127;
	}
	if (status)
		free_and_exit(status);
}

int	get_error_status(int err, char *variable)
{
	int	status;

	status = 127;
	if (err == IS_DIR)
	{
		ft_put_strjoin_fd(variable, ": Is a directory\n", 2);
		status = 126;
	}
	else if (err == X_NOK)
	{
		ft_put_strjoin_fd(variable, ": Permission denied\n", 2);
		status = 126;
	}
	else if (err == NOT_FOUND && ft_strchr(variable, '/'))
		ft_put_strjoin_fd(variable, ": No such file or directory\n", 2);
	else if (err == NOT_FOUND)
		ft_put_strjoin_fd(variable, ": command not found\n", 2);
	else if (err == EXEC_ERROR)
		ft_put_strjoin_fd(variable, ": No such file or directory\n", 2);
	return (status);
}

int	error_status(int err, char *variable, int is_fork)
{
	int	status;

	status = get_error_status(err, variable);
	if (is_fork == FORK)
		free_and_exit(status);
	return (status);
}
