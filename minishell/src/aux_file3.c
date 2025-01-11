/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_file3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 00:36:49 by lantonio          #+#    #+#             */
/*   Updated: 2025/01/11 00:40:19 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*allocate_token(void)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
	{
		free_all_mem();
		return (NULL);
	}
	collect_mem(token, MEM_TOKEN_PTR, 0);
	return (token);
}

char	*ft_strjoin_free(char *s1, const char *s2)
{
	char	*result;
	size_t	len1;
	size_t	len2;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (s1);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	result = (char *)malloc(len1 + len2 + 1);
	if (!result)
	{
		free(s1);
		return (NULL);
	}
	ft_strcpy2(result, s1);
	ft_strcat(result, s2);
	free(s1);
	return (result);
}
