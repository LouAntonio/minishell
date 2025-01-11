/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 18:17:27 by hmateque          #+#    #+#             */
/*   Updated: 2024/12/14 18:17:31 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	unset(t_node *list, char ***env_table)
{
	int		status;

	status = EXIT_SUCCESS;
	list = list->next;
	while (list)
	{
		if (is_valid_var(list->value))
			*env_table = del_env_var(*env_table, list->value);
		else
			error_builtin("unset: not a valid identifier\n", &status);
		list = list->next;
	}
	return (status);
}
