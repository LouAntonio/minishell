/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 18:20:36 by hmateque          #+#    #+#             */
/*   Updated: 2024/12/14 18:20:37 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*expand_heredoc(char *input)
{
	int		i;
	char	*expanded_var;

	i = 0;
	expanded_var = NULL;
	while (input[i])
	{
		if (input[i] == '$')
			expand_heredoc_var(&expanded_var, input, &i);
		else
			expanded_var = add_char_to_str(expanded_var, input[i++]);
	}
	return (expanded_var);
}

void	expand_heredoc_var(char **expanded_var, char *str, int *i)
{
	char	*tmp;

	*i = *i + 1;
	if (!str[*i] && *i != 1)
		*expanded_var = add_char_to_str(*expanded_var, '$');
	else if (str[*i] == '?')
	{
		tmp = ft_strdup(ft_itoa(*(exit_status())));
		if (*expanded_var)
			*expanded_var = ft_strjoin(*expanded_var, tmp);
		else
			*expanded_var = ft_strdup(tmp);
		collect_mem(*expanded_var);
		*i = *i + 1;
	}
	else if (ft_isalpha(str[*i]) || str[*i] == '_')
		expand_heredoc_std_var(expanded_var, str, i);
	else
		expand_non_std_var(expanded_var, str, i);
}

void	expand_heredoc_std_var(char **expanded_var, char *str, int *i)
{
	char	*var;
	char	*tmp;

	var = NULL;
	while (ft_isalpha(str[*i]) || str[*i] == '_')
	{
		var = add_char_to_str(var, str[*i]);
		*i = *i + 1;
	}
	tmp = getenv(var);
	if (tmp && *expanded_var)
	{
		*expanded_var = ft_strjoin(*expanded_var, tmp);
		collect_mem(*expanded_var);
	}
	else if (tmp)
	{
		*expanded_var = ft_strdup(tmp);
		collect_mem(*expanded_var);
	}
}
