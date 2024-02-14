# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tiacovel <tiacovel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/08 11:38:10 by tiacovel          #+#    #+#              #
#    Updated: 2024/02/14 16:57:25 by tiacovel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
LIBFT_DIR = lib/libft
LIBFT	= lib/libft/libft.a

SRC =	$(wildcard src/*.c)

OBJ	= $(SRC:.c=.o)

RM		= rm -f
CC		= cc
CFLAGS	= -Wall -Wextra -Werror
LINK = -Llib/libft -lft

all: $(NAME)

$(NAME): $(OBJ)
	@if [ ! -f $(LIBFT_DIR)/libft.a ]; then \
 		echo "Building libft..."; \
		make -C $(LIBFT_DIR); \
	else \
		echo "libft.a already exists."; \
	fi
		$(CC) -g -O0 $(OBJ) -Llib/libft -lft -o $(NAME)

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