/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 08:23:31 by hmateque          #+#    #+#             */
/*   Updated: 2024/12/04 10:57:30 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Função para liberar a lista ligada de variáveis de ambiente
void	free_env_list(t_env **env)
{
	t_env	*current;
	t_env	*next;

	if (!env || !*env)
		return ;
	current = *env;
	while (current)
	{
		next = current->next;
		free(current->name);
		free(current->value);
		free(current);
		current = next;
	}
	*env = NULL;
}

// Função para liberar um único comando
static void	free_command(Command *command)
{
	int	i;

	i = -1;
	if (!command)
		return ;
	free(command->command);
	if (command->args)
	{
		while (command->args[++i])
			free(command->args[i]);
		free(command->args);
	}
	free(command->redirect_out);
	free(command->redirect_in);
	free(command->heredoc_end);
	free(command);
}

// Função para liberar a lista ligada de comandos
static void	free_command_list(Command *command_list)
{
	Command	*current;
	Command	*next;

	current = command_list;
	next = NULL;
	while (current)
	{
		next = current->next;
		free_command(current);
		current = next;
	}
}

// Função para liberar a árvore de comandos
void	free_command_tree(CommandTree *command_tree)
{
	if (!command_tree)
		return ;
	free_command_list(command_tree->root);
	free(command_tree);
}

void	ft_exit(Command *command_tree, t_env **env)
{
	free_env_list(env);
	if (command_tree)
		free_command_list(command_tree);
	printf("exit\n");
	exit(0);
}

void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	if (!matrix)
		return ;
	while (matrix[i] != NULL)
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

// void	free_classified_tokens(Token **classified_tokens)
// {
// 	int	i;

// 	i = 0;
// 	if (!classified_tokens)
// 		return ;
// 	while (classified_tokens[i] != NULL)
// 	{
// 		free(classified_tokens[i]->value);
// 		free(classified_tokens[i]);
// 		i++;
// 	}
// 	free(classified_tokens);
// }
