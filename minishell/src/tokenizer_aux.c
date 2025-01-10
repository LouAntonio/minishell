/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_aux.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 22:16:19 by lantonio          #+#    #+#             */
/*   Updated: 2025/01/10 22:17:02 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_state(t_wc_state *state)
{
	state->count = 0;
	state->in_word = false;
	state->quote = '\0';
}

void	handle_quote2(char c, t_wc_state *state)
{
	if (state->quote)
	{
		if (c == state->quote)
			state->quote = '\0';
	}
	else if (c == '"' || c == '\'')
	{
		if (!state->in_word)
			state->count++;
		state->quote = c;
		state->in_word = true;
	}
}

void	handle_non_quote(char c, t_wc_state *state)
{
	if (isspace(c))
		state->in_word = false;
	else if (!state->in_word)
	{
		state->count++;
		state->in_word = true;
	}
}

int	count_words(const char *input)
{
	t_wc_state	state;
	int			i;

	init_state(&state);
	i = 0;
	while (input[i] != '\0')
	{
		if (state.quote)
			handle_quote2(input[i], &state);
		else
			handle_non_quote(input[i], &state);
		i++;
	}
	return (state.count);
}

char	*allocate_word(int capacity)
{
	return ((char *)malloc(capacity * sizeof(char)));
}
