/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 18:16:49 by hmateque          #+#    #+#             */
/*   Updated: 2024/12/14 18:16:52 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	get_signal(char **arg)
{
	char	signal;

	signal = '+';
	if (**arg == '-')
	{
		signal = '-';
		*arg = *arg + 1;
	}
	else if (**arg == '+')
		*arg = *arg + 1;
	while (**arg == '0')
		*arg = *arg + 1;
	return (signal);
}

static int	check_limit(char *arg, char signal)
{
	if (ft_strlen(arg) > 19)
		return (EXIT_FAILURE);
	else if (ft_strcmp(arg, "9223372036854775807") > 0 && signal == '+')
		return (EXIT_FAILURE);
	else if (ft_strcmp(arg, "9223372036854775808") > 0 && signal == '-')
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	check_characters(char *arg)
{
	char	signal;
	char	*tmp;

	while (*arg == ' ')
		arg++;
	if (*arg != '+' && *arg != '-' && !ft_isdigit(*arg))
		return (EXIT_FAILURE);
	if ((*arg == '+' || *arg == '-') && !ft_isdigit(*(arg + 1)))
		return (EXIT_FAILURE);
	signal = get_signal(&arg);
	tmp = arg;
	while (*arg)
	{
		if (!ft_isdigit(*arg))
			return (EXIT_FAILURE);
		arg++;
	}
	if (check_limit(tmp, signal))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	validate_exit_status(t_node *list, int *status)
{
	int			valid_exit;
	char		*arg;
	long long	num;

	valid_exit = EXIT_SUCCESS;
	arg = list->next->value;
	num = ft_atol(arg);
	if (check_characters(arg))
	{
		ft_putstr_fd("exit: ", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		*status = 2;
		return (valid_exit);
	}
	if (list->next->next)
	{
		ft_putstr_fd("exit: too many arguments\n", STDERR_FILENO);
		valid_exit = EXIT_FAILURE;
		*status = 1;
		return (valid_exit);
	}
	*status = num % 256;
	return (valid_exit);
}

int	exit_builtin(t_node *list)
{
	int	valid_exit;
	int	status;
	int	*last_exit_status;

	last_exit_status = NULL;
	valid_exit = EXIT_SUCCESS;
	ft_putstr_fd("exit\n", STDERR_FILENO);
	if (!list->next)
	{
		last_exit_status = exit_status();
		free_and_exit(*last_exit_status);
		return (*last_exit_status);
	}
	else if (list->next->value)
		valid_exit = validate_exit_status(list, &status);
	if (valid_exit == EXIT_FAILURE)
		return (1);
	free_and_exit(status);
	return (0);
}
