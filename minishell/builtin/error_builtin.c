/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 18:16:40 by hmateque          #+#    #+#             */
/*   Updated: 2024/12/14 18:16:42 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	error_builtin(char *message, int *status)
{
	if (message)
		ft_putstr_fd(message, STDERR_FILENO);
	*status = EXIT_FAILURE;
}
