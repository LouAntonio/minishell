/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 10:06:57 by lantonio          #+#    #+#             */
/*   Updated: 2025/01/11 00:40:58 by lantonio         ###   ########.fr       */
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

extern int	g_return ;

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

typedef enum s_token_type
{
	TOKEN_COMMAND,
	TOKEN_ARG,
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_APPEND_OUT,
	TOKEN_HEREDOC,
}	t_token_type;

typedef struct s_tpken
{
	t_token_type	type;
	char			*value;
}					t_token;

typedef struct s_cmd
{
	char			*command;
	char			**args;
	char			*redirect_out;
	char			*redirect_in;
	char			*heredoc_end;
	int				redirect_out_type;
	int				heredoc;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_cmd_tree
{
	t_cmd			*root;
}					t_cmd_tree;

// Tipos de alocação para identificar como liberar a memória
typedef enum e_mem_type
{
	MEM_CHAR_PTR,
	MEM_CHAR_MATRIX,
	MEM_TOKEN_PTR,
	MEM_TOKEN_MATRIX,
	MEM_COMMAND
}					t_mem_type;

// Estrutura para armazenar informações sobre a memória alocada
typedef struct s_memory
{
	void			*ptr;
	t_mem_type		type;
	size_t			size;
}					t_memory;

typedef struct s_expander_variables
{
	char			*result;
	char			*current;
	int				inside_single_quotes;
	char			*exit_status;
	char			*var_end;
	t_env			*env_var;
	char			*var_name;
}					t_expander_variables;

typedef struct s_word_data {
	char	**matrix;
	char	*word;
	int		word_len;
	int		word_capacity;
	int		word_index;
	bool	in_word;
	char	quote;
}	t_word_data;

typedef struct s_wc_state{
	int		count;
	bool	in_word;
	char	quote;
}	t_wc_state;

int					path_commands(t_cmd *cmd, t_env **env,
						char **envp, int *g_returns);
bool				validate_env(t_env **env);
bool				is_absolute_path(const char *command);
int					execute_absolute_path(t_cmd *cmd,
						char **envp, int *g_returns);
char				**get_env_paths(t_env *env);
int					try_paths(char **paths, t_cmd *cmd,
						char **envp, int *g_returns);
void				build_path(const char *dir, const char *cmd,
						char *buffer, size_t size);
int					execute_command(const char *path, char **args,
						char **envp, int *g_returns);
int					save_original_fds(int old_fd[2]);
int					restore_original_fds(int old_fd[2]);
int					execute_heredoc_child(t_cmd *cmd,
						int hd_fd[2], t_env **env);
int					setup_heredoc_parent(int hd_fd[2],
						int old_fd[2], pid_t pid);
int					handle_heredoc(t_cmd *cmd, int old_fd[2], t_env **env);
int					handle_pipe_execution(t_cmd *cmd,
						int fd[2], t_env **env, char **envp);
int					handle_pipe(t_cmd *cmd, int old_fd[2],
						t_env **env, char **envp);
int					run_commands(t_cmd *cmd, t_env **env, char **envp);

void				init_state(t_wc_state *state);
void				handle_quote2(char c, t_wc_state *state);
void				handle_non_quote(char c, t_wc_state *state);
int					count_words(const char *input);
char				*allocate_word(int capacity);
char				*ft_strcpy2(char *dest, const char *src);
char				*ft_strcat(char *dest, const char *src);
char				*resize_word(char *word, int *capacity);
int					handle_quote(t_word_data *data, char current_char);
int					finalize_quoted_word(t_word_data *data);
int					append_char_to_word(t_word_data *data, char current_char);
int					handle_quote_start(t_word_data *data, char current_char);
int					handle_space(t_word_data *data);
int					handle_regular_char(t_word_data *data, char current_char);
int					finalize_word(t_word_data *data);
void				initialize_extraction(t_word_data *data);
int					process_char(t_word_data *data, char current_char);
int					extract_words(const char *input, t_word_data *data);
char				**split_words(const char *input, int *word_count);
char				**ft_tokens(const char *input, int *word_count);

t_token				**allocate_classified_tokens(int wc);
t_token				*allocate_token(void);
char				*strip_quotes(const char *token);
void				classify_token_type(t_token **classified_tokens,
						char **tokens, int wc);

t_cmd				*initialize_command(int wordcount);
int					process_redirect_out(t_token **tokens,
						int *i, t_cmd *current);
int					process_append_out(t_token **tokens,
						int *i, t_cmd *current);
int					process_redirect_in(t_token **tokens,
						int *i, t_cmd *current);
int					process_heredoc(t_token **tokens,
						int *i, t_cmd *current);
void				process_command_args(t_token **tokens,
						int *i, t_cmd *cmd, int *index);
t_cmd				*handle_new_cmd(t_cmd **root, t_cmd *cur,
						t_token *token, int wc);
int					handle_redirections(t_token **tokens,
						int *i, t_cmd *current);
t_cmd				*build_cmd(t_token **tokens, int wordcount);

// checkers
int					identify_command(char *line, t_env **env, char **envp,
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
void				update_oldpwd_pwd(char *old_path,
						t_env **env, int *g_returns);
int					ft_export(char **command, t_env **env, int *g_returns);
int					ft_unset(char **command, t_env **env, int *g_returns);
void				ft_exit(t_env **env, int status, char *exit_status);
void				ft_env(char **args, int *g_returns, t_env **env);

// file command.c
void				create_files(t_cmd *command);
void				handle_sigint_child(int sig);
int					check_command(char *str, int *g_returns, int status);
int					check_quote_syntax_return(char *line);
char				*close_pipe(char *command, int i, int j);
int					run_commands(t_cmd *cmd, t_env **env,
						char **envp);
int					built_ins(t_cmd *cmd, t_env **env, int *g_returns);
int					check_red_in(t_cmd *cmd, int *fd_in);
int					handle_redirection(t_cmd *cmd);
int					avoid_double_quote_error(char *str);
int					avoid_single_quote_error(char *str);
char				*remove_double_quotes(char *str);
char				*remove_single_quotes(char *str);

// file aux_command_1.c
bool				should_skip_expansion(char *str);

// ft_aux_close_pipe.c
int					handle_pipe_error(char *message);
char				*read_complete_command(void);
char				*join_command(char *command, char *complete);

// env
void				print_all_var(char **env);
void				ft_list_add_back(t_env **lst, t_env *new);
t_env				*ft_list_last(t_env *lst);
char				*ft_str_ncpy(int len, char *src);
void				print_list(t_env *list, int flag);
void				search_and_print_list(t_env *list, char *str, int fd);
t_env				*find_env_var(t_env *env, char *name);

// t_token
char				**ft_tokens(const char *input, int *word_count);
t_token_type		identify_token(char *token);
t_token				**classify_tokens(char **tokens, int word_count,
						t_env **env, int *g_returns);
t_cmd				*build_cmd(t_token **tokens, int word_count);

// Liberacao de memoria
void				*allocate_mem(size_t nmemb, size_t size);
void				collect_mem(void *ptr, t_mem_type type, size_t size);
t_list				**get_mem_address(void);
void				free_all_mem(void);
void				free_env_list(t_env **env);
void				free_matrix(char **matrix);

#endif