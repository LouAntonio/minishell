# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/11 09:30:23 by hmateque          #+#    #+#              #
#    Updated: 2025/01/11 10:29:48 by lantonio         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc

CFLAGS = -Wall -Wextra -Werror

VPATH = pre_execute tree parse heredoc execute environ builtin

INCLUDE = -I./include -I ./libft 

LIBFT = ./libft/libft.a

SRC = main.c \
	check_syntax.c \
	tokenizer.c \
	tokenizer_utils.c \
	utils.c \
	check_heredoc.c \
	get_env.c \
	insert_env.c \
	delete_env.c \
	get_utils.c \
	free_env.c \
	signal.c \
	build_bin_tree.c \
	execution.c \
	parser.c \
	split_list.c \
	split_redir.c \
	find_path.c \
	execute_operator.c \
	execute_redir.c \
	exit_status.c \
	expand.c \
	expand_heredoc.c \
	pre_execute.c \
	pre_expand.c \
	re_tokenizer.c \
	handle_error.c \
	handle_fd.c \
	handle_fork.c \
	echo.c \
	cd.c \
	exit.c \
	pwd.c \
	export.c \
	export_utils.c \
	unset.c \
	env.c \
	error_builtin.c \
	create_node.c \
	handle_delimiter.c \

OBJ = obj

SRC_OBJ = $(SRC:%.c=$(OBJ)/%.o)

all: libft create_obj $(NAME)

$(NAME): $(SRC_OBJ)
	@$(CC) $(CFLAGS) $(SRC_OBJ) -lreadline $(LIBFT) -o $(NAME) 
	@echo "\033[1;32mMINISHELL COMPILED!\033[0m"

libft:
	@make -C ./libft

$(OBJ)/%.o : %.c
	@mkdir -p $(dir $@)	
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDE)

clean: 
	@make -C ./libft clean --silent
	@rm -rf $(OBJ)
	@echo "objects removed" 

fclean: clean
	@make -C ./libft fclean --silent 
	@rm -f $(NAME) $(NAME_BONUS) 
	@echo "executable removed"

re: fclean all

create_obj:
	@mkdir -p $(OBJ)/

.PHONY: all clean fclean re libft
.DEFAULT_GOAL := all