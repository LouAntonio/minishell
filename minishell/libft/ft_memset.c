/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 10:10:18 by lantonio          #+#    #+#             */
/*   Updated: 2025/01/11 10:10:19 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*str;
	unsigned char	u;

	str = (unsigned char *)s;
	u = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		str[i] = u;
		i++;
	}
	return (s);
}
