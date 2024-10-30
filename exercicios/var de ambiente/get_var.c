/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 08:28:04 by hmateque          #+#    #+#             */
/*   Updated: 2024/10/30 08:32:33 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int main(int ac, char **av)
{
    char *path;
    
    if (ac != 2)
        return (1);
    path = getenv(av[1]);
    if (path != NULL && av[1][0] != '$')
        printf("O valor de PATH é: %s\n", path);
    else
        printf("A variável PATH não está definida.\n");
    return 0;
}
