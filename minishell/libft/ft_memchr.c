/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 10:09:54 by lantonio          #+#    #+#             */
/*   Updated: 2025/01/11 10:09:55 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	size_t			i;
	unsigned char	u;

	str = (unsigned char *)s;
	u = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (str[i] == u)
			return (&str[i]);
		i++;
	}
	return (NULL);
}
