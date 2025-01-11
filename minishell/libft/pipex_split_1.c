/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_split_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbazagli <bbazagli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 18:45:48 by cogata            #+#    #+#             */
/*   Updated: 2024/04/30 18:12:30 by bbazagli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	init_quote_structs(t_flags *sing_quote, t_flags *doub_quote)
{
	sing_quote->character = '\'';
	sing_quote->status = 'c';
	sing_quote->count = 0;
	doub_quote->character = '"';
	doub_quote->status = 'c';
	doub_quote->count = 0;
}

void	is_quote(t_flags *quote, char c, int count_flag, int *count_word)
{
	quote->count = 1;
	if (quote->status == 'o')
	{
		quote->status = 'c';
		if (!c && count_flag == 0)
			*count_word = *count_word + 1;
	}
	else
		quote->status = 'o';
}

void	is_delimiter(int single_count_quote, int double_count_quote,
		int *count_flag, int *count_word)
{
	if (*count_flag == 0 && (single_count_quote == 1
			|| double_count_quote == 1))
		*count_word = *count_word + 1;
	*count_flag = 0;
}

void	is_word(int *count_word, int *count_flag)
{
	*count_word = *count_word + 1;
	*count_flag = 1;
}

int	ft_modified_count_words(char *s, char delimiter)
{
	int		i;
	int		count_word;
	int		count_flag;
	t_flags	sing;
	t_flags	doub;

	i = 0;
	count_word = 0;
	count_flag = 0;
	init_quote_structs(&sing, &doub);
	while (s[i])
	{
		if (s[i] == delimiter && sing.status == 'c' && doub.status == 'c')
			is_delimiter(sing.count, doub.count, &count_flag, &count_word);
		else if (s[i] == sing.character && doub.status == 'c')
			is_quote(&sing, s[i + 1], count_flag, &count_word);
		else if (s[i] == doub.character && sing.status == 'c')
			is_quote(&doub, s[i + 1], count_flag, &count_word);
		else if (count_flag == 0)
			is_word(&count_word, &count_flag);
		i++;
	}
	if (sing.status == 'o' || doub.status == 'o')
		return (-1);
	return (count_word);
}
