/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 10:06:57 by lantonio          #+#    #+#             */
/*   Updated: 2024/11/13 18:10:31 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define MAX_TOKENS 100
# define MAX_TOKEN_LENGTH 1000

# include "../libft/libft.h"
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <sys/wait.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef enum
{
	TOKEN_COMMAND,
	TOKEN_ARG,
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_APPEND_OUT,
}					TokenType;

typedef struct
{
	TokenType		type;
	char			*value;
}					Token;

typedef struct Command
{
	char			*command;
	char			**args;
	char			*redirect_out;
	char			*redirect_in;
	int				redirect_out_type;
	struct Command	*next;
}					Command;

typedef struct CommandTree
{
	Command			*root;
}					CommandTree;

// checkers
void				identify_command(char *command, t_env **env, char **envp);
int					check_signal_exit(char *str);
int					check_read_from(char **str);
int					check_cipher(char *str, int fd, t_env *env);
int					check_arg(char *str);
int					ft_isspace(char c);

// Signal
void				signal_new_line(int signum);
void				configure_signal(void);

// aux_funct args main
void				ft_set_value(int ac, char **av, char **env,
						t_env **all_env);
char				*ft_char_cpy(char *src, int len_src, int len_dest,
						int limit);

// aux_funct str
int					ft_strcmp(char *s1, char *s2);
void				ft_putstr_fd(char *s, int fd);
int					isset_in_mat(char **mat, char *str);
char				*remove_quote(char *str);
char				**remove_quotes(char **str);

// command
void				pwd(char **str);
void				echo(char **str, t_env *env);
void				cd(char **str);
int					ft_export(char **command, t_env **env);
int					ft_unset(char **command, t_env **env);

// env
void				print_all_var(char **env);
void				ft_list_add_back(t_env **lst, t_env *new);
t_env				*ft_list_last(t_env *lst);
char				*ft_str_ncpy(int len, char *src);
void				print_list(t_env *list, int flag);
void				search_and_print_list(t_env *list, char *str, int fd);

// Token
char				**tokenize(char *line);
TokenType			identify_token(char *token);
Token				**classify_tokens(char **tokens);
Command				*build_command_tree(Token **tokens);
int					validate_command_tree(Command *root);
char				**tokenizar(const char *str, char delimitador);
#endif