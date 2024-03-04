/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tree_main.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:14:38 by jkaller           #+#    #+#             */
/*   Updated: 2024/03/04 17:30:54 by jkaller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minish.h"
#include "../../../include/parser.h"
#include "../../../include/libft.h"
#include <unistd.h>

void	perform_reduce(t_tree_stack **tree_stack, t_table *current_row, t_table **parsing_table, t_tree_node **parsing_tree)
{
	t_tree_stack	*subtree;
	int				next_state;

	subtree = create_subtree(tree_stack, current_row->reduced_token);
	if (subtree)
	{
		if (!add_reduction_node(tree_stack, current_row->next_state))
		{
			next_state = get_next_state(parsing_table, *tree_stack);
			if (!push_state_to_stack(tree_stack, next_state))
				if (!add_subtree_to_tree(parsing_tree, &subtree, current_row->next_state))
				{
					free_stack(subtree);
					return ;
				}
		}
		free_stack(subtree);
	}
}

void	perform_shift(t_tree_stack **tree_stack, t_token **token_stack, int next_state)
{
	push_token_to_stack(tree_stack, *token_stack);
	push_state_to_stack(tree_stack, next_state);
	*token_stack = (*token_stack)->next;
}

t_tree_node	*create_syntax_tree(t_token *token_stack,
			t_table **parsing_table)
{
	int				process_done_flag;
	t_tree_stack	*tree_stack;
	t_token			*start_of_token_stack;
	t_table			*next_row;
	t_tree_node		*parsing_tree;

	process_done_flag = 0;
	start_of_token_stack = token_stack;
	tree_stack = intialise_stack();
	parsing_tree = NULL;
	while (process_done_flag == 0)
	{
		next_row = get_next_row(*parsing_table, tree_stack, token_stack);
		if (next_row && next_row->action == SHIFT)
			perform_shift(&tree_stack, &token_stack, next_row->next_state);
		else if (next_row && next_row->action == REDUCE)
			perform_reduce(&tree_stack, next_row, parsing_table, &parsing_tree);
		else if (next_row && next_row->action == ACCEPT)
			process_done_flag = 1;
		else
		{
			ft_printf("Syntax Error\n");
			free_all(*parsing_table, start_of_token_stack, parsing_tree);
			exit(-1); 
		}
	}
	free_stack(tree_stack);
	return (clarify_grammar_types(parsing_tree));
}
