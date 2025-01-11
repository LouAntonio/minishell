/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 18:22:38 by hmateque          #+#    #+#             */
/*   Updated: 2024/12/14 18:22:39 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

int	*exit_status(void)
{
	static int	status;

	return (&status);
}

int	update_exit_status(int status)
{
	int	*ptr;

	ptr = exit_status();
	*ptr = status;
	return (*ptr);
}
