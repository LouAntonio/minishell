/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_args_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 10:34:06 by hmateque          #+#    #+#             */
/*   Updated: 2024/10/30 11:34:54 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_set_value(int ac, char **av, char **env, t_env **all_env)
{
	int		i;
	t_env	*new;

	i = -1;
	(void)ac;
	(void)av;
	while (env[++i] != NULL)
	{
		new = (t_env *)malloc(sizeof(t_env));
		ft_lstadd_back(all_env, new);
	}
}

char	*ft_strncpy(const char *src, int limit)
{
	int i;
	int len_src;
	char *dest;

	i = 0;
	len_src = ft_strlen(src);
	if (limit)
	{
		while (src[i] != '\0' && src[i] != '=')
			i++;
		if (i == len_src)
			return (NULL);
		while (src[++i] != '\0')
			dest[i] = src[i];
		dest[i] = '\0';
		return (dest);
	}
}