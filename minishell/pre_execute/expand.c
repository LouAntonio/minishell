/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 18:21:54 by hmateque          #+#    #+#             */
/*   Updated: 2024/12/14 18:21:55 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*expand(t_node *node)
{
	int		i;
	char	*str;
	char	*expanded_var;

	i = 0;
	expanded_var = NULL;
	str = node->value;
	while (str[i])
	{
		if (str[i] == '$')
			expand_var(node, &expanded_var, str, &i);
		else
			expanded_var = add_char_to_str(expanded_var, str[i++]);
	}
	return (expanded_var);
}

void	expand_var(t_node *node, char **expanded_var, char *str, int *i)
{
	char	*tmp;

	*i = *i + 1;
	if (!str[*i] && (node->next_char == ' ' || node->next_char == '\n'
			|| node->next_char == '\t' || node->next_char == '\0'))
		*expanded_var = add_char_to_str(*expanded_var, '$');
	else if (str[*i] == '?')
	{
		tmp = ft_itoa(*(exit_status()));
		if (*expanded_var)
			*expanded_var = ft_strjoin(*expanded_var, tmp);
		else
			*expanded_var = ft_strdup(tmp);
		collect_mem(*expanded_var);
		free(tmp);
		*i = *i + 1;
	}
	else if (ft_isalpha(str[*i]) || str[*i] == '_')
		expand_std_var(expanded_var, str, i);
	else if (str[*i])
		expand_non_std_var(expanded_var, str, i);
}

void	expand_std_var(char **expanded_var, char *str, int *i)
{
	char	*var;
	char	*tmp;

	var = NULL;
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
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

void	expand_non_std_var(char **expanded_var, char *str, int *i)
{
	char	*var;

	(void)var;
	*expanded_var = add_char_to_str(*expanded_var, str[*i - 1]);
	while (str[*i] && str[*i] != '$')
	{
		*expanded_var = add_char_to_str(*expanded_var, str[*i]);
		*i = *i + 1;
	}
}

char	*add_char_to_str(char *str, char c)
{
	int		i;
	int		len;
	char	*tmp;

	len = 0;
	if (str)
		len = ft_strlen(str);
	tmp = str;
	str = malloc(len + 2);
	collect_mem(str);
	i = 0;
	while (tmp && tmp[i])
	{
		str[i] = tmp[i];
		i++;
	}
	str[i] = c;
	str[i + 1] = '\0';
	return (str);
}
