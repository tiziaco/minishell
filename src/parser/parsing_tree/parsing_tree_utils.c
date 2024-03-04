/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tree_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 19:29:01 by jkaller           #+#    #+#             */
/*   Updated: 2024/03/04 17:32:56 by jkaller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minish.h"
#include "../../../include/parser.h"
#include "../../../include/libft.h"
#include <unistd.h>

int	get_next_state(t_table	**parsing_table, t_tree_stack *tree_stack)
{
	t_table	*current_row;
	int		row_index;
	int		state;
	int		next_state;

	current_row = *parsing_table;
	row_index = 0;
	state = tree_stack->next->next_state;
	while (row_index <= PARSING_TABLE_LENGTH)
	{
		if (current_row->state == state)
		{
			if (current_row->token_grammar_type == tree_stack->grammar_type) 
			{
				return (current_row->next_state);
			}
			else if (current_row->token_grammar_type == -1)
				next_state = current_row->next_state;
		}
		row_index++;
		current_row++;
	}
	return (next_state);
}

t_table	*get_next_row(t_table *parsing_table, t_tree_stack *tree_stack, t_token *token_stack)
{
	t_table	*current_row;
	int		row_index;
	t_table	*return_row;
	int		token_type;

	if (!tree_stack)
		return (NULL);
	return_row = NULL;
	token_type = -1;
	if (token_stack)
		token_type = token_stack->type;
	current_row = parsing_table;
	row_index = 0;
	while (row_index < PARSING_TABLE_LENGTH)
	{
		if (current_row->state == tree_stack->next_state)
		{
			if (current_row->token_grammar_type == token_type)
				return (current_row);
			else if (current_row->token_grammar_type == -1)
				return_row = current_row;
		}
		row_index++;
		current_row++;
	}
	return (return_row);
}

t_tree_stack	*intialise_stack()
{
	t_tree_stack	*start_of_stack;

	start_of_stack = (t_tree_stack *)malloc(sizeof(*start_of_stack));
	if (!start_of_stack)
		exit(-1);
	start_of_stack->token_value = NULL;
	start_of_stack->grammar_type = -1;
	start_of_stack->next_state = 0;
	start_of_stack->next = NULL;
	return (start_of_stack);
}

void	print_parsing_tree(t_tree_node *root, int depth)
{
	int	i;

	if (root == NULL)
		return ;
	i = 0;
	while (i < depth)
	{
		i++;
		ft_printf("  ");
	}
	ft_printf("%i: Leaf Header: %d, Grammar Type: %d, Token Value: %s\n",
		depth, root->leaf_header, root->grammar_type, root->token_value);
	print_parsing_tree(root->left, depth + 1);
	print_parsing_tree(root->right, depth + 1);
}
