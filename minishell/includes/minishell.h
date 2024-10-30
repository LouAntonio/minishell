/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 10:06:57 by lantonio          #+#    #+#             */
/*   Updated: 2024/10/30 10:57:54 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}					t_env;

# include "../libft/libft.h"
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

// checkers
int					check_signal_exit(char *str);
int					check_read_from(char **str);

// Signal
void				signal_new_line(int signum);
void				configure_signal(void);

// aux_funct args main
void				ft_set_value(int ac, char **av, char **env, t_env **all_env);

// aux_funct str
int					ft_strcmp(char *s1, char *s2);
void				ft_putstr_fd(char *s, int fd);
int					isset_in_mat(char **mat, char *str);

// command
void				pwd(char **str);
void				echo(char **str);
void				identify_command(char *command);

// env
void				print_all_var(char **env);

#endif