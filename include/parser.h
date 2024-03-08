/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 17:41:25 by jkaller           #+#    #+#             */
/*   Updated: 2024/03/08 21:11:54 by jkaller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <limits.h>
# include <stdbool.h>
# include "libft.h"
# include "minish.h"

# define PARSING_TABLE_LENGTH 100 // make it so this is not hardcoded
# define PARSING_TABLE_PATH "/data/parsing_table"
//# define PARSING_TABLE_PATH "/../data/parsing_table" // !!! For debugging only !!!

// Parsing Tree

typedef struct s_tree_node {
	int leaf_header;
	int grammar_type;
	char *token_value;
	struct s_tree_node *next;
	struct s_tree_node *left;
	struct s_tree_node *right;
} t_tree_node;

typedef struct s_tree_stack {
	int grammar_type;
	int next_state;
	char *token_value;
	struct s_tree_stack *next;
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

typedef enum
{
	TREE_ROOT = -2,
	TREE_CMD = 0,
	TREE_RED_TO = 1,
	TREE_RED_FROM = 2,
	TREE_DLESS = 3,
	TREE_DGREAT = 4,
	TREE_PIPE = 5,
	TREE_PARAM = 6,
	TREE_FILE = 7,
	TREE_LIMITER = 8
}	TreeTypes;

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
t_tree_node	*create_syntax_tree(t_token *token_stack,
			t_table **parsing_table);
// parsing_tree_utils
t_tree_stack	*intialise_stack();
t_table	*get_next_row(t_table *parsing_table, t_tree_stack *tree_stack, t_token *token_stack);
int		get_next_state(t_table	**parsing_table, t_tree_stack *tree_stack);
// shift operation utils
void	push_token_to_stack(t_tree_stack **tree_stack, t_token *token_stack);
int	push_state_to_stack(t_tree_stack **tree_stack, int next_state);
// reduce operation utils
int	add_subtree_to_tree(t_tree_node **parsing_tree, t_tree_stack **subtree, int reduced_token);
int	add_reduction_node(t_tree_stack **tree_stack, int reduction_token);
t_tree_stack	*create_subtree(t_tree_stack **tree_stack, int tokens_to_reduce);
// reduce operation utils 2
t_tree_node	*transform_stack_to_node(t_tree_stack *subtree);
t_tree_node	*search_for_subtree(t_tree_node **parsing_tree, int reduced_token);
// list utils
void	subtree_add_back(t_tree_stack **subtree, t_tree_stack *tree_stack);

/* Initialization functions */
int	tokenize_input(char *input_line, t_token **token_stack);

/* Utility functions */
void	ft_lstadd_back_token(t_token **lst, t_token *new);
t_token	*ft_lstnew_token(char *value, TokenTypes token_type);
void	print_token_stack(t_token *token_stack);

// Parse parsing table to data structure
void print_parsing_tree(t_tree_node *root, int depth);

//clean up
t_tree_node	*clarify_grammar_types(t_tree_node *parsing_tree);
void	free_syntax_tree(t_tree_node *abstract_syntax_tree);
void	free_token_stack(t_token *token_stack);
void	free_stack(t_tree_stack *tree_stack);


//tree to cmd

#endif