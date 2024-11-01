/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 10:28:57 by hmateque          #+#    #+#             */
/*   Updated: 2024/11/01 09:20:31 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**tokenizar(const char *str, char delimitador)
{
	char	**tokens;
	int		token_count;
	int		inside_quotes;
	char	*temp;
	int		temp_index;

	tokens = malloc(MAX_TOKENS * sizeof(char *));
	token_count = 0;
	inside_quotes = 0;
	temp = malloc(ft_strlen(str) + 1);
	temp_index = 0;
	for (int i = 0; str[i] != '\0'; i++)
	{
		if (str[i] == '"')
			inside_quotes = !inside_quotes;
		if (inside_quotes)
			temp[temp_index++] = str[i];
		else
		{
			if (str[i] == delimitador)
			{
				if (temp_index > 0)
				{
					temp[temp_index] = '\0';
					tokens[token_count++] = strdup(temp);
					temp_index = 0;
				}
			}
			else
				temp[temp_index++] = str[i];
		}
	}
	if (temp_index > 0)
	{
		temp[temp_index] = '\0';
		tokens[token_count++] = strdup(temp);
	}
	free(temp);
	tokens[token_count] = NULL;
	return (tokens);
}

void	identify_command(char *command, t_env **env)
{
	char	**str;

	str = tokenizar(command, ' ');
	str = remove_quotes(str);
	if (str)
	{
		if (str[0])
		{
			if (!ft_strcmp(str[0], "pwd"))
				pwd(str);
			else if (!ft_strcmp(str[0], "echo"))
				echo(str, *env);
			else if (!ft_strcmp(str[0], "env"))
				print_list(*env, 1);
			else if (!ft_strcmp(str[0], "export"))
				ft_export(str, env);
			else if (!ft_strcmp(str[0], "unset"))
				ft_unset(str, env);
			else if (!ft_strcmp(str[0], "exit"))
				exit(0);
		}
	}
	else
		printf("Error\n");
}
