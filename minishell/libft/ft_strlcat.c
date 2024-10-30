/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 08:34:03 by hmateque          #+#    #+#             */
/*   Updated: 2024/05/15 08:57:13 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	space_left;
	size_t	i;
	char	*s;

	s = (char *)src;
	dst_len = 0;
	src_len = 0;
	while (dst_len < size && dst[dst_len] != '\0')
		dst_len++;
	while (s[src_len] != '\0')
		src_len++;
	if (dst_len == size)
		return (size + src_len);
	space_left = size - dst_len;
	i = 0;
	while (i < space_left - 1 && src[i] != '\0')
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	dst[dst_len + i] = '\0';
	return (dst_len + src_len);
}
