/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_split_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cogata <cogata@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 18:47:25 by cogata            #+#    #+#             */
/*   Updated: 2024/04/12 14:07:33 by cogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	is_quote_init_letter(char **words, t_word *aux, t_flags *first,
		t_flags *second)
{
	if (second->status == 'o')
	{
		words[aux->i][aux->count_letters] = aux->s[aux->j];
		aux->count_letters = aux->count_letters + 1;
	}
	else
	{
		if (first->status == 'o')
			first->status = 'c';
		else
			first->status = 'o';
	}
}

void	check_and_init_letters(char **words, t_word *aux, t_flags *sing,
		t_flags *doub)
{
	if (aux->s[aux->j] == sing->character)
		is_quote_init_letter(words, aux, sing, doub);
	else if (aux->s[aux->j] == doub->character)
		is_quote_init_letter(words, aux, doub, sing);
	else
	{
		words[aux->i][aux->count_letters] = aux->s[aux->j];
		aux->count_letters = aux->count_letters + 1;
	}
}

void	ft_init_modified_words(char *s, char **words, char delimiter,
		int count_word)
{
	t_word	aux;
	t_flags	sing;
	t_flags	doub;

	aux.i = 0;
	aux.j = 0;
	aux.s = s;
	init_quote_structs(&sing, &doub);
	while (aux.i < count_word)
	{
		aux.count_letters = 0;
		while (s[aux.j] == delimiter)
			aux.j = aux.j + 1;
		while (s[aux.j] && !(s[aux.j] == delimiter && sing.status == 'c'
				&& doub.status == 'c'))
		{
			check_and_init_letters(words, &aux, &sing, &doub);
			aux.j = aux.j + 1;
		}
		words[aux.i][aux.count_letters] = '\0';
		aux.i++;
	}
	words[aux.i] = NULL;
}

char	**remove_quotes(char *s, char delimiter)
{
	int		count_word;
	char	**words;

	if (s == NULL)
		return (0);
	count_word = ft_modified_count_words(s, delimiter);
	if (count_word == -1)
	{
		ft_put_strjoin_fd("Invalid command. Dquote mechanism is not available.",
			NULL, 2);
		return (NULL);
	}
	words = malloc((count_word + 1) * sizeof(char *));
	if (words == NULL)
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}
	ft_count_letters(s, words, delimiter, count_word);
	ft_init_modified_words(s, words, delimiter, count_word);
	return (words);
}
