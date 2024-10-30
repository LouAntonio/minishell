/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 08:57:30 by hmateque          #+#    #+#             */
/*   Updated: 2024/05/16 09:17:31 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *ptr, int value, size_t num)
{
	unsigned char	*p;
	unsigned char	v;
	size_t			i;

	i = 0;
	p = (unsigned char *)ptr;
	v = (unsigned char)value;
	while (i < num)
	{
		if (p[i] == v)
			return ((void *)(ptr + i));
		i++;
	}
	return (NULL);
}
