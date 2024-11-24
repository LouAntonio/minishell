/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 10:30:56 by hmateque          #+#    #+#             */
/*   Updated: 2024/11/19 15:09:08 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_read_from(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (!ft_strcmp(str[i], "<") || !ft_strcmp(str[i], "<<"))
			return (1);
	return (0);
}

int	check_arg(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (0);
	i++;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	check_cipher(char *str, int fd, t_env *env)
{
	int		i;
	char	*result;
	char	*new_str;

	i = 0;
	result = ft_strchr(str, '$');
	if (result == NULL)
		return (0);
	result++;
	while (result[i] != '\0')
		i++;
	new_str = (char *)malloc(sizeof(char) * (i + 1));
	i = 0;
	while (result[i] != '\0')
	{
		new_str[i] = result[i];
		i++;
	}
	new_str[i] = '\0';
	search_and_print_list(env, new_str, fd);
	free(new_str);
	return (1);
}

int	ft_isspace(char c)
{
	if (c == ' ')
		return (1);
	if (c == '\t')
		return (1);
	if (c == '\n')
		return (1);
	if (c == '\v')
		return (1);
	if (c == '\f')
		return (1);
	if (c == '\r')
		return (1);
	return (0);
}

char	*trim_spaces(char *str)
{
	char	*start;
	char	*end;
	char	*trimmed;
	int		new_length;

	if (!str)
		return (NULL);
	start = str;
	while (*start && ft_isspace((unsigned char)*start))
		start++;
	if (*start == '\0')
		return (NULL);
	end = str + ft_strlen(str) - 1;
	while (end > start && ft_isspace((unsigned char)*end))
		end--;
	new_length = end - start + 1;
	trimmed = (char *)malloc(new_length + 1);
	if (!trimmed)
		return (NULL);
	ft_strncpy(trimmed, start, new_length);
	trimmed[new_length] = '\0';
	return (trimmed);
}

char	*ft_strncpy(char *dest, const char *src, int n)
{
	int	i;

	i = 0;
	while (i < n && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}
