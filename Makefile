# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/08 11:38:10 by tiacovel          #+#    #+#              #
#    Updated: 2024/03/21 15:36:01 by jkaller          ###   ########.fr        #
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
		$(wildcard src/parser/expansion/*.c) \
		$(wildcard src/parser/parsing_tree/*.c) \
		$(wildcard src/parser/cleanup/*.c) \
		$(wildcard src/parser/tree_to_commands/*.c) \
		$(wildcard src/init/*.c)

OBJ	= $(SRC:.c=.o)

RM		= rm -f
CC		= cc
CFLAGS	= #-Wall -Wextra -Werror
LINK_DIR = -Llib/libft -L/opt/homebrew/opt/readline/lib
LINK_LIB =  -lft -lreadline
INCLUDE = -I /opt/homebrew/opt/readline/include
HIDE = @

# Color and styles
COLOR_RESET = \033[0m
BOLD_GREEN = \033[1;32m
GREEN = \033[0;32m
RED = \033[0;31m

all: $(NAME)

$(NAME): $(OBJ)
	@if [ ! -f $(LIBFT_DIR)/libft.a ]; then make -C $(LIBFT_DIR); fi
	@echo "$(GREEN)libft COMPILED.$(COLOR_RESET)"
	$(HIDE) $(CC) -g -O0 $(OBJ) $(LINK_DIR) $(INCLUDE) -o $(NAME) $(LINK_LIB)
	@echo "$(BOLD_GREEN)PROGRAM COMPILED 🥳$(COLOR_RESET)"

src/%.o: src/%.c
	$(HIDE) $(CC) -g -O0 $(CFLAGS) $(INCLUDE) -c $< -o $@
	@echo "$(GREEN)Compiling$(COLOR_RESET)  $< .."

clean:
	$(HIDE) make clean -C lib/libft
	$(HIDE) $(RM) $(OBJ)
	@echo "$(RED)Minish objs removed.$(COLOR_RESET)"
fclean: clean
	$(HIDE) @make fclean -C lib/libft > /dev/null
	$(HIDE) $(RM) $(NAME) > /dev/null
	@echo "$(RED)Minish fully cleaned.$(COLOR_RESET)"

re: fclean all

.PHONY: all clean fclean re