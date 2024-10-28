# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/11 16:35:01 by lantonio          #+#    #+#              #
#    Updated: 2024/10/28 12:01:54 by hmateque         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell
CC		= cc
FLAGS	= -Wall -Wextra -Werror

SRCS	= minishell.c\
			./src/funts_aux.c\
			./checkers/signal.c\
			./signal/signal.c\
			./commands/pwd.c\
			./commands/echo.c\

OBJS	= $(SRCS:.c=.o)

$(NAME): $(OBJS)
	@$(CC) $(FLAGS) $(OBJS) -Iincludes -o $(NAME) -lreadline
	@echo "\033[1;32mSUCESS"

%.o:%.c
	@$(CC) $(FLAGS) -c $< -o $@

all: $(NAME)

clean :
	@rm -rf $(OBJS)
	@echo "Cleaning objects"

fclean : clean
	@rm -rf $(NAME)
	@echo "cleaning executable"

re : fclean all

.PHONY : all clean fclean re