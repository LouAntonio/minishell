/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_aux_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 11:56:22 by hmateque          #+#    #+#             */
/*   Updated: 2024/12/12 12:22:51 by hmateque         ###   ########.fr       */
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

char *ft_strjoin_free(char *s1, const char *s2)
{
    char *result;
    size_t len1, len2;

    if (!s1 && !s2)
        return NULL;
    if (!s1)
        return strdup(s2);
    if (!s2)
        return s1;

    len1 = strlen(s1);
    len2 = strlen(s2);

    result = (char *)malloc(len1 + len2 + 1);
    if (!result)
    {
        free(s1);
        return NULL;
    }

    strcpy(result, s1);
    strcat(result, s2);

    free(s1);
    return result;
}

char *ft_strndup(const char *s, size_t n)
{
    char *result;
    size_t len;

    if (!s)
        return NULL;

    len = strlen(s);
    if (n < len)
        len = n;

    result = (char *)malloc(len + 1);
    if (!result)
        return NULL;

    ft_memcpy(result, s, len);
    result[len] = '\0';

    return result;
}