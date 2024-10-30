/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 12:16:45 by hmateque          #+#    #+#             */
/*   Updated: 2024/05/21 12:51:38 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nbrlen(long n)
{
	int	strlen;

	strlen = 0;
	if (n == 0)
		return (1);
	else if (n < 0)
	{
		strlen++;
		n *= -1;
	}
	while (n > 0)
	{
		n /= 10;
		strlen++;
	}
	return (strlen);
}

char	*ft_itoa(int n)
{
	int		len;
	long	nbr;
	char	*str;

	nbr = n;
	len = ft_nbrlen(nbr);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	*(str + len--) = '\0';
	if (nbr == 0)
	{
		*(str + 0) = '0';
	}
	else if (nbr < 0)
	{
		nbr *= -1;
		*(str + 0) = '-';
	}
	while (nbr > 0)
	{
		*(str + len--) = (48 + (nbr % 10));
		nbr /= 10;
	}
	return (str);
}
