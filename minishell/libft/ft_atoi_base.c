/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 10:07:11 by lantonio          #+#    #+#             */
/*   Updated: 2025/01/11 10:07:13 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ishex(char c)
{
	if (c >= '0' && c <= '9')
		return (c - 48);
	else if (c >= 'a' && c <= 'f')
		return (c - 87);
	else if (c >= 'A' && c <= 'F')
		return (c - 55);
	return (-1);
}

int	ft_atoi_base(char *str)
{
	int	i;
	int	sign;
	int	decimal;
	int	num;

	i = 0;
	sign = 1;
	decimal = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	num = ishex(str[i]);
	while (num >= 0)
	{
		decimal = decimal * 16 + num;
		i++;
		num = ishex(str[i]);
	}
	return (sign * decimal);
}
