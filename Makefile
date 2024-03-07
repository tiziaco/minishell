
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
		$(wildcard src/parser_old/*.c) $(wildcard src/redirections/*.c) \
		$(wildcard src/parser/*.c) $(wildcard src/parser/tokenizer/*.c) \
		$(wildcard src/parser/parsing_table/*.c) \
		$(wildcard src/parser/parsing_tree/*.c) \
		$(wildcard src/parser/cleanup/*.c) \
		$(wildcard src/parser/tree_to_commands/*.c)

OBJ	= $(SRC:.c=.o)

RM		= rm -f
CC		= cc
CFLAGS	= #-Wall -Wextra -Werror
LINK_DIR = -Llib/libft -L/opt/homebrew/opt/readline/lib
LINK_LIB =  -lft -lreadline
INCLUDE = -I /opt/homebrew/opt/readline/include
HIDE = @

all: $(NAME)

$(NAME): $(OBJ)
	@if [ ! -f $(LIBFT_DIR)/libft.a ]; then \
		$(HIDE) make -C $(LIBFT_DIR); \
	fi
		@echo "\033[0;32mlibft COMPILED.\033[0m"
		$(HIDE) $(CC) -g -O0 $(OBJ) $(LINK_DIR) $(INCLUDE) -o $(NAME) $(LINK_LIB)
		@echo "\033[1;32mPROGRAM COMPILED 🥳\033[0m"

src/%.o: src/%.c
	$(HIDE) $(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	@echo "\033[0;32mCompiling\033[0m  $< .."

clean:
	$(HIDE) make clean -C lib/libft
	$(HIDE) $(RM) $(OBJ)
	@echo "\033[0;31mObjs removed.\n\033[0m"
fclean: clean
	$(HIDE) @make fclean -C lib/libft
	$(HIDE) $(RM) $(NAME)
	@echo "\033[0;31mFull clean.\n\033[0m"

re: fclean all

.PHONY: all clean fclean re