/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 08:23:31 by hmateque          #+#    #+#             */
/*   Updated: 2024/12/11 15:37:24 by lantonio         ###   ########.fr       */
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

int	ft_atoi_stop(char *nptr, int *stop)
{
	int	i;
	int	sign;
	int	nb;

	i = 0;
	*stop = 0;
	while (nptr[i] == ' ' || nptr[i] == '\f' || nptr[i] == '\n'
		|| nptr[i] == '\r' || nptr[i] == '\t' || nptr[i] == '\v')
		i++;
	sign = 1;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign *= -1;
		i++;
	}
	nb = 0;
	while (nptr[i])
	{
		if (!(nptr[i] >= '0' && nptr[i] <= '9'))
			return (*stop = 1, nb);
		nb = nb * 10 + nptr[i] - '0';
		i++;
	}
	return (nb * sign);
}

void	ft_exit(Command *command_tree, t_env **env)
{
	int	exit_status;
	int	stop;

	if (matrix_len(command_tree->args) == 2)
	{
		exit_status = ft_atoi_stop(command_tree->args[1], &stop);
		if (stop)
		{
			printf("minishell: exit: %s: numeric argument required\n", command_tree->args[1]);
			exit_status = 2;
		}
	}
	else
	{
		printf("exit\n");
		if (matrix_len(command_tree->args) > 2)
		{
			printf("minishell: exit: too many arguments\n");
			return ;
		}
	}
	free_env_list(env);
	//if (command_tree)
		//free_command_list(command_tree);
	//printf("exit\n");
	exit(exit_status);
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

void	free_classified_tokens(Token **classified_tokens)
{
	int	i;

	i = 0;
	if (!classified_tokens)
		return ;
	while (classified_tokens[i] != NULL)
	{
		free(classified_tokens[i]->value);
		free(classified_tokens[i]);
		i++;
	}
	free(classified_tokens);
}
