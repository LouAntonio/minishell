/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_split_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 10:14:20 by lantonio          #+#    #+#             */
/*   Updated: 2025/01/11 10:14:23 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	is_quote_letter(char *first_status, char second_status,
		int *count_letters)
{
	if (second_status == 'o')
		*count_letters = *count_letters + 1;
	else
	{
		if (*first_status == 'o')
			*first_status = 'c';
		else
			*first_status = 'o';
	}
}

void	check_character(t_flags *sing, t_flags *doub, int *count_letters,
		char c)
{
	if (c == sing->character)
		is_quote_letter(&sing->status, doub->status, count_letters);
	else if (c == doub->character)
		is_quote_letter(&doub->status, sing->status, count_letters);
	else
		*count_letters = *count_letters + 1;
}

void	ft_count_letters(char *s, char **words, char delimiter, int count_word)
{
	int		i;
	int		j;
	int		count_letters;
	t_flags	sing;
	t_flags	doub;

	i = 0;
	j = 0;
	init_quote_structs(&sing, &doub);
	while (i < count_word)
	{
		count_letters = 0;
		while (s[j] == delimiter)
			j++;
		while (s[j] && !(s[j] == delimiter && sing.status == 'c'
				&& doub.status == 'c'))
		{
			check_character(&sing, &doub, &count_letters, s[j]);
			j++;
		}
		words[i] = malloc(count_letters + 1);
		i++;
	}
}
