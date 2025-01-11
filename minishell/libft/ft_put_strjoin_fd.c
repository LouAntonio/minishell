/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_strjoin_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 10:10:44 by lantonio          #+#    #+#             */
/*   Updated: 2025/01/11 10:10:44 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_put_strjoin_fd(char *str1, char *str2, int fd)
{
	int		buffer_size;
	char	*buffer;

	if (fd > 0 && str1 != 0 && str2 != 0)
	{
		buffer_size = ft_strlen(str1) + ft_strlen(str2);
		buffer = ft_strjoin(str1, str2);
		write(fd, buffer, buffer_size);
		free(buffer);
	}
	else if (fd > 0 && str1 != 0)
	{
		buffer_size = ft_strlen(str1);
		buffer = str1;
		write(fd, buffer, buffer_size);
	}
}
