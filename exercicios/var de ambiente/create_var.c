/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 08:35:58 by hmateque          #+#    #+#             */
/*   Updated: 2024/10/30 08:51:01 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int main(int ac, char **av)
{
    if (ac != 3)
    {
        printf("Erro: ./a.out nome_var valor_var\n");
        exit(1);
    }
    if (setenv(av[1], av[2], 0) == 0)
        printf("NOVA_VAR foi criada com sucesso!\n");
    else
    {
        printf("Erro ao criar variável de ambiente\n");
        exit(1);
    }
    char *nova_var = getenv(av[1]);
    if (nova_var != NULL)
        printf("NOVA_VAR: %s\n", nova_var);
    return 0;
}
