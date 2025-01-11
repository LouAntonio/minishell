/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 18:19:43 by hmateque          #+#    #+#             */
/*   Updated: 2024/12/14 18:19:43 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	*save_fd(void)
{
	int	*fd;

	fd = ft_calloc(sizeof(int), 3);
	fd[IN] = dup(STDIN_FILENO);
	fd[OUT] = dup(STDOUT_FILENO);
	fd[ERR] = dup(STDERR_FILENO);
	collect_mem(fd);
	return (fd);
}

void	reset_fd(int *fd)
{
	dup2(fd[IN], STDIN_FILENO);
	close(fd[IN]);
	dup2(fd[OUT], STDOUT_FILENO);
	close(fd[OUT]);
	dup2(fd[ERR], STDERR_FILENO);
	close(fd[ERR]);
}
