/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_args_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 10:34:06 by hmateque          #+#    #+#             */
/*   Updated: 2024/11/19 15:38:43 by lantonio         ###   ########.fr       */
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
		new->name = ft_char_cpy(env[i], 0, 0, 1);
		new->value = ft_char_cpy(env[i], 0, 0, 2);
		ft_list_add_back(all_env, new);
	}
}

char	*ft_char_cpy(char *src, int len_src, int len_dest, int limit)
{
	int		i;
	int		j;
	char	*dest;

	i = 0;
	len_src = ft_strlen(src);
	while (src[i] != '\0' && src[i] != '=')
		i++;
	if (i == len_src)
	{
		dest = ft_str_ncpy(len_src, src);
		return (dest);
	}
	if (limit == 1)
	{
		dest = ft_str_ncpy(i, src);
		return (dest);
	}
	len_dest = len_src - i - 1;
	dest = (char *)malloc(sizeof(char) * (len_dest + 1));
	j = 0;
	while (src[++i] != '\0')
		dest[j++] = src[i];
	dest[j] = '\0';
	return (dest);
}

char	*ft_str_ncpy(int len, char *src)
{
	int		j;
	char	*str;

	j = -1;
	str = (char *)malloc(sizeof(char) * (len + 1));
	while (++j < len)
		str[j] = src[j];
	str[len] = '\0';
	return (str);
}
