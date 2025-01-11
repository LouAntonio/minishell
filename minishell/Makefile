# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/11 09:30:23 by hmateque          #+#    #+#              #
#    Updated: 2025/01/11 09:30:25 by hmateque         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

NAME_BONUS = minishell_bonus

CC = cc

CFLAGS = -Wall -Wextra -Werror -g3

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

all: verify libft create_obj $(NAME)

bonus: verify libft create_obj $(NAME_BONUS)

verify: libft $(SRC_OBJ) 
	@if [ -d "./minishell/" ]; then \
		rm -rf "minishell/"; \
	fi
	@if [ -d "./minishell_bonus/" ]; then \
		rm -rf "minishell_bonus/"; \
	fi

$(NAME): $(SRC_OBJ)
	@$(CC) $(CFLAGS) $(SRC_OBJ) -lreadline $(LIBFT) -o $(NAME) 
	@echo "Compilation completed: $@"

$(NAME_BONUS): $(SRC_OBJ) 
	@$(CC) $(CFLAGS) $(SRC_OBJ) -lreadline $(LIBFT) -o $(NAME_BONUS) 
	@echo "Compilation completed: $@"

libft:
	make -C ./libft

$(OBJ)/%.o : %.c
	@mkdir -p $(dir $@)	
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDE) && printf "Compiling: $(notdir $<\n)"

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

valgrind: all
	valgrind --suppressions=readline.supp  --leak-check=full --show-leak-kinds=all --track-origins=yes ./minishell

val:
	valgrind -q --leak-check=full --show-leak-kinds=all --track-origins=yes \
	--track-fds=yes --suppressions=readline.supp --trace-children=yes \
	--trace-children-skip=/usr/*,./*,*/bin/* ./minishell

.PHONY: all clean fclean re libft
.DEFAULT_GOAL := all