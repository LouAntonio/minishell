/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 10:11:51 by lantonio          #+#    #+#             */
/*   Updated: 2025/01/11 10:11:52 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dest_len;
	size_t	src_len;
	size_t	total_len;
	int		i;

	if (dst != 0)
		dest_len = ft_strlen(dst);
	else
		dest_len = 0;
	src_len = ft_strlen(src);
	total_len = src_len + dest_len;
	i = 0;
	if (size > dest_len)
	{
		while (dest_len < size - 1 && src[i] != '\0')
		{
			dst[dest_len] = src[i];
			dest_len++;
			i++;
		}
		dst[dest_len] = '\0';
		return (total_len);
	}
	return (src_len + size);
}
