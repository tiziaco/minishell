
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/08 11:38:10 by tiacovel          #+#    #+#              #
#    Updated: 2024/03/02 00:09:55 by jkaller          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
LIBFT_DIR = lib/libft

SRC =	$(wildcard src/*.c) $(wildcard src/builtins/*.c) \
		$(wildcard src/env/*.c) $(wildcard src/errors/*.c) \
		$(wildcard src/execution/*.c) $(wildcard src/outils/*.c) \
		$(wildcard src/parser/*.c) $(wildcard src/redirections/*.c) \
		$(wildcard src/parsing/*.c) $(wildcard src/parsing/tokenizer/*.c) \
		$(wildcard src/parsing/parsing_table/*.c) \
		$(wildcard src/parsing/parsing_tree/*.c) \
		$(wildcard src/parsing/cleanup/*.c)

OBJ	= $(SRC:.c=.o)

RM		= rm -f
CC		= cc
CFLAGS	= #-Wall -Wextra -Werror
LINK = -Llib/libft -lft -lreadline

all: $(NAME)

$(NAME): $(OBJ)
	@if [ ! -f $(LIBFT_DIR)/libft.a ]; then \
 		echo "Building libft..."; \
		make -C $(LIBFT_DIR); \
	else \
		echo "libft.a already exists."; \
	fi
		$(CC) -g -O0 $(OBJ) $(LINK) -o $(NAME)

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@make clean -C lib/libft
	$(RM) $(OBJ)

fclean: clean
	@make fclean -C lib/libft
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re