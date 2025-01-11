/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 18:23:13 by hmateque          #+#    #+#             */
/*   Updated: 2024/12/14 18:23:14 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_node	*last_node(t_node *list)
{
	t_node	*last;

	last = list;
	while (last->next)
		last = last->next;
	return (last);
}

void	free_and_exit(int status)
{
	char	*cwd;

	free_mem(get_mem_address());
	free_mem(get_env_address());
	cwd = update_cwd(NULL);
	if (cwd)
	{
		free(cwd);
		cwd = NULL;
	}
	exit(status);
}

void	print_env_table(char **env_table)
{
	int	i;

	i = 0;
	while (env_table[i])
	{
		printf("%s\n", env_table[i]);
		i++;
	}
}

void	clean_tmp_files(void)
{
	int		i;
	char	*num;
	char	*temp_path;

	i = 0;
	num = ft_itoa(i);
	collect_mem(num);
	temp_path = ft_strjoin("/tmp/.here_", num);
	collect_mem(temp_path);
	while (access(temp_path, F_OK) == 0)
	{
		unlink(temp_path);
		i++;
		num = ft_itoa(i);
		collect_mem(num);
		temp_path = ft_strjoin("/tmp/.here_", num);
		collect_mem(temp_path);
	}
}
