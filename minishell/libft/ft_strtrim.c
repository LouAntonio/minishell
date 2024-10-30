/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 09:13:54 by hmateque          #+#    #+#             */
/*   Updated: 2024/05/21 09:32:52 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_in_set(char c, const char *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	len;
	size_t	i;
	char	*start;
	char	*end;
	char	*str_strimmed;

	if (s1 == NULL || set == NULL)
		return (NULL);
	start = (char *)s1;
	end = (char *)(s1 + ft_strlen(s1) - 1);
	while (*start && is_in_set(*start, set))
		start++;
	while (end > start && is_in_set(*end, set))
		end--;
	len = end - start + 1;
	str_strimmed = (char *)malloc(len + 1);
	if (str_strimmed == NULL)
		return (NULL);
	i = -1;
	while (++i < len)
		str_strimmed[i] = start[i];
	str_strimmed[len] = '\0';
	return (str_strimmed);
}
