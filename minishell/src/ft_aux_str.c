/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_aux_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 11:56:22 by hmateque          #+#    #+#             */
/*   Updated: 2025/01/11 00:40:10 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	isset_in_mat(char **mat, char *str)
{
	int	i;

	i = -1;
	while (mat[++i])
		if (!ft_strcmp(mat[i], str))
			return (i);
	return (0);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] && s2[i])
		i++;
	return ((int)((unsigned char)s1[i] - (unsigned char)s2[i]));
}

char	*ft_strcpy2(char *dest, const char *src)
{
	char	*start;

	start = dest;
	while (*src)
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';
	return (start);
}

char	*ft_strcat(char *dest, const char *src)
{
	char	*start;

	start = dest;
	while (*dest)
		dest++;
	while (*src)
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';
	return (start);
}

char	*ft_strndup(const char *s, size_t n)
{
	char	*result;
	size_t	len;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	if (n < len)
		len = n;
	result = (char *)malloc(len + 1);
	if (!result)
		return (NULL);
	collect_mem(result, MEM_CHAR_PTR, 0);
	ft_memcpy(result, s, len);
	result[len] = '\0';
	return (result);
}
