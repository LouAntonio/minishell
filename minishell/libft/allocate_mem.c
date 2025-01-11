/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate_mem.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cogata <cogata@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 16:57:04 by bbazagli          #+#    #+#             */
/*   Updated: 2024/05/15 10:46:44 by cogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	**get_mem_address(void)
{
	static t_list	*ptr;

	return (&ptr);
}

void	collect_mem(void *content)
{
	ft_lstadd_back(get_mem_address(), ft_lstnew(content));
}

void	*allocate_mem(size_t nmemb, size_t size)
{
	void	*content;

	content = ft_calloc(nmemb, size);
	if (content == NULL)
		exit(ENOMEM);
	collect_mem(content);
	return (content);
}

t_list	**get_env_address(void)
{
	static t_list	*ptr;

	return (&ptr);
}

void	collect_env_mem(char **env_table)
{
	int	i;

	if (get_env_address())
		free_mem(get_env_address());
	i = 0;
	ft_lstadd_back(get_env_address(), ft_lstnew((void *)env_table));
	while (env_table[i])
	{
		ft_lstadd_back(get_env_address(), ft_lstnew((void *)env_table[i]));
		i++;
	}
}
