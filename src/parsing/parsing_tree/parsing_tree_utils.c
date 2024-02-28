/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tree_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 19:29:01 by jkaller           #+#    #+#             */
/*   Updated: 2024/02/28 20:22:26 by jkaller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minish.h"
#include "../../../include/parsing.h"
#include "../../../include/libft.h"
#include <unistd.h>

int	get_next_state(t_table	**parsing_table, t_tree_stack *tree_stack)
{
	t_table	*current_row;
	int		row_index;
	int		state;

	current_row = *parsing_table;
	row_index = 0;
	state = tree_stack->next->next_state;
	while (row_index <= PARSING_TABLE_LENGTH)
	{
		if (current_row->state == state && (current_row->token_grammar_type == tree_stack->grammar_type || current_row->token_grammar_type == -1)) 
			return (current_row->next_state);
		row_index++;
		current_row++;
	}
	return (-1); // add proper error_managemnt
}

t_table	*get_next_row(t_table	*parsing_table, t_tree_stack *tree_stack, t_token *token_stack)
{
	t_table	*current_row;
	int		row_index;

	current_row = parsing_table;
	row_index = 0;
	while (row_index <= PARSING_TABLE_LENGTH)
	{
		if (current_row->state == tree_stack->next_state && (current_row->token_grammar_type == token_stack->type || current_row->token_grammar_type == -1)) 
			return (current_row);
		row_index++;
		current_row++;
	}
	return (NULL);
}

t_token	*get_next_token(t_token *token_stack)
{
	static t_token	*next_token = NULL;
	t_token			*current_token;

	if (next_token == NULL)
		next_token = token_stack;
	current_token = next_token;
	next_token = next_token->next;
	//ft_printf("Token Type: %d\n", current_token->type);
	return (current_token);
}

void	intialise_stack_and_tree(t_tree_node *tree_node, t_tree_stack *tree_stack)
{
	tree_node->grammar_type = 0;
	tree_node->token_value = NULL;
	tree_node->next = NULL;
	tree_node->left = NULL;
	tree_node->right = NULL;

	tree_stack->grammar_type = 0;
	tree_stack->next_state = 0;
	tree_stack->next = NULL;
}