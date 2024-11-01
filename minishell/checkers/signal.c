/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 11:28:51 by hmateque          #+#    #+#             */
/*   Updated: 2024/11/01 09:22:25 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_signal_exit(char *str)
{
	if (str == NULL)
	{
		rl_clear_history();
		return (1);
	}
	return (0);
}
