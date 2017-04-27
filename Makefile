# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/03/13 13:03:38 by sfranc            #+#    #+#              #
#    Updated: 2017/04/27 18:59:00 by sfranc           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
SRCS_PATH = srcs
OBJS_PATH = objs
SRCS = 	$(addprefix $(SRCS_PATH)/, main.c \
		user_input.c \
		parsing_command.c \
		parsing_command2.c \
		execution.c \
		builtin_echo.c \
		builtin_env.c \
		builtin_exit.c \
		builtin_setenv.c \
		builtin_unsetenv.c \
		list_minishell.c)
OBJS =  $(SRCS:$(SRCS_PATH)/%.c=$(OBJS_PATH)/%.o)
INCLUDES = includes ../libft/libft_gitperso/includes
LIB = $(LIB_PATH)/libft.a
LIB_PATH = ../libft/libft_gitperso
# LIB_PATH = ./libft
CC = gcc
# FLAGS = -Wall -Wextra -Werror -g -fsanitize=address
FLAGS = -Wall -Wextra -Werror
# GREEN = \033[01;32m
# YELLOW = \033[01;33m
# CYAN = \033[01;36m
# RESET = \033[00m

all: $(NAME)

$(NAME): $(LIB) $(OBJS)
	$(CC) $(FLAGS) -o $@ $^

$(LIB):
	make -C $(LIB_PATH)

$(OBJS_PATH)/%.o: $(SRCS_PATH)/%.c $(INCLUDES)
	$(CC) $(FLAGS) -o $@ -c $< $(addprefix -I , $(INCLUDES))

clean:
	make clean -C $(LIB_PATH)
	rm -f $(OBJS)

fclean: clean
	make fclean -C $(LIB_PATH)
	rm -f $(NAME)

re: fclean all

git:
	git status
	git add $(SRCS) Makefile includes/minishell.h
	git commit -m "automatic commit"
	git push
	git status

.PHONY: clean fclean re