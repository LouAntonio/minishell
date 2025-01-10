/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander_variable.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:04:59 by hmateque          #+#    #+#             */
/*   Updated: 2025/01/10 17:37:24 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	expand_single_quotes(t_expander_variables *vars)
{
	vars->inside_single_quotes = !vars->inside_single_quotes;
	vars->result = ft_strjoin_free(vars->result, ft_strndup(vars->current, 1));
	vars->current++;
}

void	expand_dollar_sign(t_expander_variables *vars, t_env *env,
		int *g_returns)
{
	vars->current++;
	if (*vars->current == '?')
	{
		vars->exit_status = ft_itoa(*g_returns);
		vars->result = ft_strjoin_free(vars->result, vars->exit_status);
		free(vars->exit_status);
		vars->current++;
	}
	else
	{
		vars->var_end = vars->current;
		while (*vars->var_end && (ft_isalnum(*vars->var_end)
				|| *vars->var_end == '_'))
			vars->var_end++;
		vars->var_name = ft_strndup(vars->current, vars->var_end
				- vars->current);
		vars->env_var = find_env_var(env, vars->var_name);
		if (vars->env_var)
			vars->result = ft_strjoin_free(vars->result, vars->env_var->value);
		vars->current = vars->var_end;
	}
}

void	expand_regular_character(t_expander_variables *vars)
{
	vars->result = ft_strjoin_free(vars->result, ft_strndup(vars->current, 1));
	vars->current++;
}

char	*expand_variable(char *var, t_env *env, int *g_returns)
{
	t_expander_variables	vars;

	vars.result = ft_strdup("");
	vars.current = var;
	vars.inside_single_quotes = 0;
	while (*vars.current)
	{
		if (*vars.current == '\'')
			expand_single_quotes(&vars);
		else if (*vars.current == '$' && !vars.inside_single_quotes)
			expand_dollar_sign(&vars, env, g_returns);
		else
			expand_regular_character(&vars);
	}
	return (vars.result);
}
