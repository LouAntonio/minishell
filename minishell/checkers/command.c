/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 10:28:57 by hmateque          #+#    #+#             */
/*   Updated: 2024/11/06 16:33:21 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void print_command_tree(Command *root) {
    Command *current = root;

    while (current != NULL) {
        // Imprime o comando principal em verde
        printf("Comando: \033[0;32m%s\033[0m\n", current->command);

        // Imprime os argumentos, se houver, em azul
        printf("Argumentos:");
        int i = 0;
        while (current->args[i] != NULL) {
            printf(" \033[0;34m%s\033[0m", current->args[i]);
            i++;
        }
        printf("\n");

        // Imprime o redirecionamento de saída, se houver, em amarelo
        if (current->redirect_out != NULL) {
            printf("Redirecionamento de saída: \033[0;33m%s\033[0m\n", current->redirect_out);
        }

        // Imprime o redirecionamento de entrada, se houver, em amarelo
        if (current->redirect_in != NULL) {
            printf("Redirecionamento de entrada: \033[0;33m%s\033[0m\n", current->redirect_in);
        }

        // Se há um próximo comando no pipeline, imprime uma seta indicando
        if (current->next != NULL) {
            printf("|\n|\nV\n");
        }

        // Move para o próximo comando na árvore
        current = current->next;
    }
}

void	identify_command(char *command, t_env **env)
{
    Token   **classified_tokens;
	char	**str;
    
	str = tokenize(command);
	classified_tokens = classify_tokens(str);
	
	Command *command_tree = build_command_tree(classified_tokens);
   
    int i = 0;
    while (classified_tokens[i] != NULL)
    {
        printf("Token: \033[0;32m%s\033[0m, Tipo: \033[0;31m%d\033[0m\n", classified_tokens[i]->value, classified_tokens[i]->type);
        i++;
    }
	
	if (validate_command_tree(command_tree)) {
        printf("Comando válido e pronto para execução.\n");
    } else {
        printf("Comando inválido.\n");
    }
	print_command_tree(command_tree);
	(void)env;
	//str = remove_quotes(str);
	// if (str)
	// {
	// 	if (str[0])
	// 	{
	// 		if (!ft_strcmp(str[0], "pwd"))
	// 			pwd(str);
	// 		else if (!ft_strcmp(str[0], "echo"))
	// 			echo(str, *env);
	// 		else if (!ft_strcmp(str[0], "env"))
	// 			print_list(*env, 1);
	// 		else if (!ft_strcmp(str[0], "export"))
	// 			ft_export(str, env);
	// 		else if (!ft_strcmp(str[0], "unset"))
	// 			ft_unset(str, env);
	// 		else if (!ft_strcmp(str[0], "exit"))
	// 			exit(0);
	// 	}
	// }
	// else
	// 	printf("Error\n");
}
