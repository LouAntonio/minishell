/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 10:30:56 by hmateque          #+#    #+#             */
/*   Updated: 2025/01/10 18:33:37 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

char	*trim_spaces(char *str, size_t i)
{
	char	*start;
	char	*end;
	char	*trimmed;
	size_t	new_length;

	if (!str)
		return (NULL);
	start = str;
	while (*start && ft_isspace((unsigned char)*start))
		start++;
	if (*start == '\0')
		return (free(str), NULL);
	end = str + ft_strlen(str) - 1;
	while (end > start && ft_isspace((unsigned char)*end))
		end--;
	new_length = end - start + 1;
	trimmed = allocate_mem(new_length + 1, sizeof(char));
	collect_mem(trimmed, MEM_CHAR_PTR, 0);
	while (++i < new_length)
		trimmed[i] = start[i];
	trimmed[new_length] = '\0';
	free(str);
	return (trimmed);
}
