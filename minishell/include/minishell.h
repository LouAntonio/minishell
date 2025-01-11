/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 18:21:06 by hmateque          #+#    #+#             */
/*   Updated: 2024/12/14 18:21:09 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <ctype.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

extern volatile int	g_signal;

# define READ 0
# define WRITE 1
# define FORK 1
# define CONSULT -1

# define IN 0
# define OUT 1
# define ERR 2

enum				e_token
{
	AND = 1,
	OR,
	PIPE,
	IN_REDIR,
	OUT_REDIR,
	APPEND,
	HEREDOC,
	WORD,
	EXPAND,
	SING_QUOTE,
	DOUB_QUOTE,
	OPEN_PAR,
	CLOSE_PAR,
};

enum				e_error
{
	FOUND = 1,
	NOT_FOUND,
	X_NOK,
	IS_DIR,
	EXEC_ERROR,
};

typedef struct s_node
{
	char			*value;
	int				type;
	char			next_char;
	struct s_node	*next;
	struct s_node	*prev;
}					t_node;

typedef struct s_tree
{
	t_node			*list;
	struct s_tree	*right;
	struct s_tree	*left;
}					t_tree;

// Signal functions
void				sigquit_ign(int signo);
void				sigint_ign(int signo);
void				sigint_handler(int signo);
void				sigint_cmd_handler(int signo);
void				sigpipe_handler(int signo);

// Parser functions
void				parse(char *input, t_tree **root);
t_node				*tokenizer(char *input);
t_node				*split_token(char **input);
void				add_token(t_node **head, t_node *node);
void				lookfor_token(t_node **node, char **input, char *temp,
						int i);
void				lookfor_meta(t_node **node, char **input, char *temp,
						int i);
t_node				*lookfor_word(char **input, int type);
t_node				*lookfor_quotes(char **input, char symbol, int type);
void				init_node(t_node **node, char *str);
t_node				*create_meta_node(char **input, char *str, int move);
t_node				*create_word_node(char *value, int type, char next_char);

// Syntax functions
int					check_quote_syntax(char *input);
int					check_par_syntax(int par_count, t_node *node);
int					check_syntax(t_node *node);
int					error_check(t_node *node);

// Tree functions
void				build_tree(t_tree **root, t_node *list);
void				create_node(t_node *list, t_tree **root);
t_node				**split_list(t_node *list);
t_node				*lookfor_operator(t_node *last);
t_node				*lookfor_and_or(t_node *last);
t_node				*lookfor_pipe(t_node *last);
t_node				*lookfor_redir(t_node *list);
void				update_prev_and_after(t_node *redir, t_node *after);
void				update_after(t_node *after, t_node **ptr_list,
						t_node **list);
t_node				**split_redir(t_node *list, t_node **ptr_list,
						t_node *redir);

// Pre-execution function
int					pre_execute(t_tree *root, char ***env_table);
t_node				*retokenizer(char **words);
char				*rejoin(t_tree *root);
void				collect_words_mem(char **words);
void				preprocess_expansion(t_node *node);

// Execution functions
char				**find_paths(char *cmd);
char				*check_paths(char **paths, char *cmd);
void				specific_errors(char *cmd);
int					check_file_status(int status, char *cmd, struct stat sb);
int					get_error_status(int err, char *variable);
int					specific_errors_file(char *file);
int					check_bin_access(char *path_name);
char				**list_to_array(t_node *head);
int					execute(t_tree *root, char ***env_table);
int					execute_tree(t_tree *root, char ***env_table);
int					execute_and_or(t_tree *root, char ***env_table);
int					execute_pipe(t_tree *root, char ***env_table);
int					execute_command(t_tree *root);
int					check_status(t_tree *root, int status);
void				fork_process(int dup_fd, int std_fd, int close_fd,
						t_tree *root);
int					update_fork(int fork_status);
int					*is_fork(void);
int					handle_error(char *message);
void				open_fork(int *fork_id, int *fd, t_tree *root,
						char ***env_table);
void				execute_fork_right(int fd1, int fd2, t_tree *root,
						char ***env_table);
void				execute_fork_left(int fd1, int fd2, t_tree *root,
						char ***env_table);
void				execute_child(int status, t_tree *root);
t_node				*remove_parentheses(t_node *list);
int					execute_par(t_tree *root, char ***env_table);

// Redir functions
int					check_file(t_tree *root);
int					execute_redir(t_tree *root, char ***env_table);
int					execute_redir_out_append(t_tree *root);
int					execute_redir_in(t_tree *root);
int					*save_fd(void);
void				reset_fd(int *fd);

// Heredoc functions
void				sigquit_received(void);
int					create_heredoc_temp(t_node *node);
int					check_delimiter(int fd, t_node *head, char *heredoc_input,
						char *delimiter);
void				check_heredoc(t_node *head);
void				check_quote_delimiter(t_node *head, char **delimiter);
void				join_delimiter(t_node *node);
void				clean_tmp_files(void);

// Expansion functions
char				*add_char_to_str(char *str, char c);
char				*expand(t_node *node);
void				expand_var(t_node *node, char **expanded_var, char *str,
						int *i);
void				expand_std_var(char **expanded_var, char *str, int *i);
void				expand_non_std_var(char **expanded_var, char *str, int *i);
char				*expand_heredoc(char *input);
void				expand_heredoc_var(char **expanded_var, char *str, int *i);
void				expand_heredoc_std_var(char **expanded_var, char *str,
						int *i);

// Builtins functions
int					execute_builtin(t_tree *root, char ***env_table);
char				*get_pwd(void);
int					pwd(void);
char				**static_cwd(void);
char				*update_cwd(char *new_pwd);
int					echo(t_node *list);
int					exit_builtin(t_node *list);
void				free_and_exit(int status);
int					cd(t_node *list, char ***env_table);
int					is_valid_var(char *str);
int					is_there_equal(char *str);
char				**find_key_value(char *str);
int					export(t_node *list, char ***env_table);
char				*add_quote_and_join(char *str);
char				**copy_table(char **original);
int					current_is_first(char *current, char *next);
void				ordenate_table(char **table);
void				print_detail_table(char **env_table);
int					unset(t_node *list, char ***env_table);
int					env(t_node *list, char **env_table);
char				**insert_env_var(char **env_table, char *key, char *value);
char				**insert_if_has_value(char **env_table, char *key,
						char *value);
char				**insert_if_has_no_value(char **env_table, char *key);
char				**add_env_var(char **env_table, char *var_line);
char				**modify_env_var(char **env_table, char *var_new_line,
						char *var_old_line);
char				**del_env_var(char **env_table, char *key);
char				**update_env_table(char **env_table, char *var_line,
						int size);
char				**get_env_table(void);
int					compare_var(char *s1, char *s2);
int					find_key(char *key, char **env_table);
void				error_builtin(char *message, int *status);
char				*update_cwd(char *new_pwd);

// Utils functions
t_node				*last_node(t_node *list);
int					*exit_status(void);
int					update_exit_status(int status);
int					error_status(int err, char *variable, int is_fork);

#endif