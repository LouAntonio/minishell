/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 10:06:57 by lantonio          #+#    #+#             */
/*   Updated: 2024/12/15 06:54:59 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_result
{
	char			*result;
	size_t			res_index;
}					t_result;

typedef struct s_quote_state
{
	int				dob_quote;
	int				sin_quote;
}					t_quote_state;

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
	TOKEN_HEREDOC,
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
	char			*heredoc_end;
	int				redirect_out_type;
	int				heredoc;
	struct Command	*next;
}					Command;

typedef struct CommandTree
{
	Command			*root;
}					CommandTree;

// checkers
void				identify_command(char *command, t_env **env, char **envp,
						int *g_returns);
int					check_read_from(char **str);
int					check_cipher(char *str, int fd, t_env *env);
int					check_arg(char *str);
int					ft_isspace(char c);
int					matrix_len(char **matrix);
char				*expand_variable(char *var, t_env *env, int *g_returns);
char				**expander(char **str, t_env *env, int *g_returns,
						int wordcount);

// Signal
void				signal_new_line(int signum);
void				signal_new_line_2(int signum);
void				configure_signal(void);

// aux_funct args main
void				ft_set_value(int ac, char **av, char **env,
						t_env **all_env);
char				*ft_char_cpy(char *src, int len_src, int len_dest,
						int limit);
char				*ft_strncpy(char *dest, const char *src, int n);
char				*trim_spaces(char *str, size_t i);

// aux_funct str
int					ft_strcmp(char *s1, char *s2);
int					isset_in_mat(char **mat, char *str);
int					check_quote_syntax(char *input);
char				*ft_strjoin_free(char *s1, const char *s2);
char				*ft_strndup(const char *s, size_t n);

// commands
void				pwd(char **str, int *g_returns);
void				echo(char **str, int *g_returns);
int					cd(char **str, int *g_returns, t_env **env);
int					ft_export(char **command, t_env **env, int *g_returns);
int					ft_unset(char **command, t_env **env, int *g_returns);
void				ft_exit(Command *command_tree, t_env **env);
void				ft_env(char **args, int *g_returns, t_env **env);

// env
void				print_all_var(char **env);
void				ft_list_add_back(t_env **lst, t_env *new);
t_env				*ft_list_last(t_env *lst);
char				*ft_str_ncpy(int len, char *src);
void				print_list(t_env *list, int flag);
void				search_and_print_list(t_env *list, char *str, int fd);
t_env				*find_env_var(t_env *env, const char *name);

// Token
char				**ft_tokens(const char *input, int *word_count);
TokenType			identify_token(char *token);
Token				**classify_tokens(char **tokens, int word_count,
						t_env **env, int *g_returns);
Command				*build_command_tree(Token **tokens, int word_count);

// Liberacao de memoria
void				*allocate_mem(size_t nmemb, size_t size);
void				collect_mem(void *content);
t_list				**get_mem_address(void);
void				free_all_mem(void);
// void				free_command_tree(CommandTree *command_tree);
void				free_env_list(t_env **env);
void				free_matrix(char **matrix);
void				free_classified_tokens(Token **classified_tokens);

#endif