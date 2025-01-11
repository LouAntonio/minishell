/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 18:16:04 by hmateque          #+#    #+#             */
/*   Updated: 2024/12/14 18:16:09 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	check_n_flag(char *arg)
{
	if (*arg == '-' && *(arg + 1) == 'n')
	{
		arg++;
		while (*arg == 'n')
			arg++;
		if (*arg == '\0')
			return (1);
	}
	return (0);
}

static void	print_args(char **args)
{
	while (*args)
	{
		ft_putstr_fd(*args, STDOUT_FILENO);
		if (*(args + 1))
			ft_putchar_fd(' ', STDOUT_FILENO);
		args++;
	}
}

int	echo(t_node *list)
{
	int		n_flag;
	char	**args;

	n_flag = 0;
	args = NULL;
	if (list->next)
	{
		args = list_to_array(list->next);
		while (*args && check_n_flag(*args))
		{
			n_flag = 1;
			args++;
		}
		print_args(args);
	}
	if (!n_flag)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
