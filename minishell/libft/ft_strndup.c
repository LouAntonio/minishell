/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 10:12:18 by lantonio          #+#    #+#             */
/*   Updated: 2025/01/11 10:12:19 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(char *s, size_t n)
{
	char	*dest;
	int		i;

	dest = ft_calloc(1, n + 1);
	if (dest == NULL)
		return (NULL);
	i = 0;
	while (n != 0 && s[i])
	{
		dest[i] = s[i];
		i++;
		n--;
	}
	dest[i] = '\0';
	return (dest);
}
