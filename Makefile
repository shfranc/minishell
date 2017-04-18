# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/03/13 13:03:38 by sfranc            #+#    #+#              #
#    Updated: 2017/04/18 16:44:52 by sfranc           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
SRCS_PATH = srcs
OBJS_PATH = objs
SRCS = 	$(addprefix $(SRCS_PATH)/, main.c)
OBJS =  $(SRCS:$(SRCS_PATH)/%.c=$(OBJS_PATH)/%.o)
INCLUDES = includes ../libft/libft_gitperso/includes
LIB = $(LIB_PATH)/libft.a
LIB_PATH = ../libft/libft_gitperso
# LIB_PATH = ./libft
CC = gcc
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

.PHONY: clean fclean re