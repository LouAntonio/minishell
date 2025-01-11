/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 10:11:21 by lantonio          #+#    #+#             */
/*   Updated: 2025/01/11 10:11:22 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchr(const char *s, int c)
{
	int				i;
	char			*str;
	unsigned char	u;

	str = (char *)s;
	u = (unsigned char)c;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == u)
		{
			return (&str[i]);
		}
		i++;
	}
	if (str[i] == c)
		return (&str[i]);
	return (0);
}
