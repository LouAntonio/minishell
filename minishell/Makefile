# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/11 16:35:01 by lantonio          #+#    #+#              #
#    Updated: 2024/12/03 11:37:04 by hmateque         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell
CC		= cc
FLAGS	= -Wall -Wextra -Werror -g

LIBFT_DIR = ./libft
LIBFT_A = $(LIBFT_DIR)/libft.a

SRCS	= minishell.c\
			./src/ft_aux_str.c\
			./src/ft_args_main.c\
			./src/tokenizer.c\
			./src/build_command.c\
			./env/list_manipulation.c\
			./checkers/command.c\
			./checkers/string.c\
			./signal/signal.c\
			./commands/pwd.c\
			./commands/echo.c\
			./commands/export.c\
			./commands/unset.c\
			./commands/cd.c\
			./commands/exit.c\
			./env/print_var.c\

OBJS	= $(SRCS:.c=.o)

$(NAME): $(OBJS) $(LIBFT_A)
	@$(CC) $(FLAGS) $(OBJS) $(LIBFT_A) -Iincludes -o $(NAME) -lreadline
	@echo "\033[1;32mSUCESS!\033[0m"

%.o:%.c
	@$(CC) $(FLAGS) -c $< -o $@

$(LIBFT_A):
	@$(MAKE) -C $(LIBFT_DIR)

all: $(NAME)

run : $(NAME)
	@echo "\033[1;32mMINISHELL_RUNNING..."
	@./minishell


clean :
	@rm -rf $(OBJS)
	@$(MAKE) clean -C $(LIBFT_DIR)
	@echo "Cleaning objects"

fclean : clean
	@rm -rf $(NAME)
	@$(MAKE) fclean -C $(LIBFT_DIR)
	@echo "cleaning executable"

re : fclean all

.PHONY : all clean fclean re