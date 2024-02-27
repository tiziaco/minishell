/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 17:41:25 by jkaller           #+#    #+#             */
/*   Updated: 2024/02/27 16:36:47 by jkaller          ###   ########.fr       */
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

# define PARSING_TABLE_LENGTH 100 // make it so this is not hardcoded
# define PARSING_TABLE_PATH "src/parsing/files/parsing_table.txt"

// Parsing Tree

typedef struct s_tree_node {
	int grammar_type;
	char *token_value;
	struct s_tree_node *parent;
	struct s_tree_node *left;
	struct s_tree_node *right;
} t_tree_node;

typedef struct s_tree_stack {
	int grammar_type;
	int state;
	char *token_value;
	struct t_tree_stack *next;
	struct t_tree_stack *previous;
} t_tree_stack;

// Parsing Table

typedef enum
{
	SHIFT = 0,
	REDUCE = 1,
	ACCEPT = 2
}	GrammarActions;

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

typedef struct s_table
{
	int				state;
	int				token_grammar_type;
	int				action;
	int				next_state;
	int				reduced_token;
}	t_table;

// Tokenizer

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

typedef struct s_token
{
	char			*value;
	int				type;
	struct s_token	*next;
}	t_token;

/* Parsing Tree */
int    create_binary_tree(t_token *token_stack, 
			t_table *parsing_table, t_tree_node **parsing_tree);
void	parse_to_stack(t_token *token_stack,
			t_table *parsing_table, t_tree_stack *tree_stack);
t_token	*get_next_token(t_token *token_stack);


/* Initialization functions */
int parse_input(int argc, char *argv[]);
int	tokenize_input(int argc, char *argv[], t_token **token_stack);

/* Utility functions */
void	ft_lstadd_back_token(t_token **lst, t_token *new);
t_token	*ft_lstnew_token(char *value, TokenTypes token_type);
void	free_token_stack(t_token *token_stack);
void	print_token_stack(t_token *token_stack);

// Parse parsing table to data structure
void	parse_table(char *path, t_table *parsing_table);

#endif