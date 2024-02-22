/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 17:41:25 by jkaller           #+#    #+#             */
/*   Updated: 2024/02/22 19:59:06 by jkaller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <limits.h>
# include <stdbool.h>

# include "libft.h"

typedef enum
{
	SHIFT = 0,
	REDUCE = 1,
	ACCEPT = 2
}	GrammarActions;

typedef	enum
{
	WORD_TOKEN = 10,
	PIPE_TOKEN = 11,
	REDIRECTION_INPUT_TOKEN = 12, // '<'
	REDIRECTION_OUTPUT_TOKEN = 13, // '>'
	REDIRECTION_HEREDOC_TOKEN = 14, // '<<'
	REDIRECTION_APPEND_TOKEN = 15, // '>>'
	END_TOKEN = 16,
} TokenTypes;

typedef enum
{
	PIPE_SEQUENCE = 100,
	SIMPLE_COMMAND = 101,
	CMD_NAME = 102,
	CMD_WORD = 103,
	CMD_PREFIX = 104,
	CMD_SUFFIX = 105,
	IO_REDIRECT = 106,
	IO_FILE = 107,
	FILENAME = 108,
	IO_HERE = 109,
	HERE_END = 110
}	GrammarTypes;

typedef struct s_token
{
	char			*value;
	TokenTypes		type;
	struct s_token	*next;
}	t_token;

/* Initialization functions */
int parse_input(int argc, char *argv[]);
int	tokenize_input(int argc, char *argv[], t_token **token_stack);

/* Utility functions */
void	ft_lstadd_back_token(t_token **lst, t_token *new);
t_token	*ft_lstnew_token(char *value, TokenTypes token_type);
void	free_token_stack(t_token *token_stack);
void	print_token_stack(t_token *token_stack);

#endif