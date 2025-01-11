/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_strjoin_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cogata <cogata@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 14:12:09 by cogata            #+#    #+#             */
/*   Updated: 2024/04/12 14:12:16 by cogata           ###   ########.fr       */
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
