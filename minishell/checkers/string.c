/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 10:30:56 by hmateque          #+#    #+#             */
/*   Updated: 2024/10/30 10:31:20 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_read_from(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (!ft_strcmp(str[i], "<") || !ft_strcmp(str[i], "<<"))
			return (1);
	return (0);
}