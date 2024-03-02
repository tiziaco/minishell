/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tree_main.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:14:38 by jkaller           #+#    #+#             */
/*   Updated: 2024/03/02 01:07:34 by jkaller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minish.h"
#include "../../../include/parsing.h"
#include "../../../include/libft.h"
#include <unistd.h>

// void	clear_stack(t_tree_stack *stack)
// {
// 	t_tree_stack	*next;

// 	while (stack)
// 	{
// 		next = stack->next;
// 		free(stack->token_value);
// 		free(stack);
// 		stack = next;
// 	}
// }

void	perform_reduce(t_tree_stack **tree_stack, t_table *current_row, t_table **parsing_table, t_tree_node **parsing_tree)
{
	t_tree_stack	*subtree;
	int				next_state;

	//subtree = (t_tree_stack *)malloc(sizeof(t_tree_stack));
	subtree = create_subtree(tree_stack, current_row->reduced_token);
	if (subtree)
	{
		if (!add_reduction_node(tree_stack, current_row->next_state))
		{
			next_state = get_next_state(parsing_table, *tree_stack);
			//ft_printf("next_state: %d\n", next_state);
			if (!push_state_to_stack(tree_stack, next_state))
				if (add_subtree_to_tree(parsing_tree, &subtree, current_row->next_state))
				{
					//clear_stack(subtree);
					return ;
				}
		}
	}
}

void	perform_shift(t_tree_stack **tree_stack, t_token **token_stack, int next_state)
{
	push_token_to_stack(tree_stack, *token_stack);
	push_state_to_stack(tree_stack, next_state);
	*token_stack = (*token_stack)->next;
}

void	create_binary_tree(t_token *token_stack,
			t_table **parsing_table, t_tree_node **parsing_tree)
{
	int				process_done_flag;
	t_tree_stack	*tree_stack;
	t_token			*start_of_token_stack;
	t_table 		*next_row;
	t_tree_node		**parsing_tree;
	
	process_done_flag = 0;
	start_of_token_stack = token_stack;
	tree_stack = intialise_stack();
	while (process_done_flag == 0)
	{
		ft_printf("DEBUG STACK START: state=%d, token type=%d\n", tree_stack->next_state, tree_stack->grammar_type);
		next_row = get_next_row(*parsing_table, tree_stack, token_stack);
		//ft_printf("DEBUG ROW START: state=%d, next_state=%d, token type=%d, action=%d\n", next_row->state, next_row->next_state, next_row->token_grammar_type, next_row->action);
		if (next_row && next_row->action == SHIFT)
		{
			perform_shift(&tree_stack, &token_stack, next_row->next_state);
			//ft_printf("DEBUG AFTER SHIFT: state=%d, token type=%d\n", tree_stack->next_state, tree_stack->grammar_type);
		}
		else if (next_row && next_row->action == REDUCE)
		{
			perform_reduce(&tree_stack, next_row, parsing_table, parsing_tree);
			//ft_printf("DEBUG AFTER REDUCE: state=%d, token type=%d\n", tree_stack->next_state, tree_stack->grammar_type);
		}
		else if (next_row && next_row->action == ACCEPT)
		{
			process_done_flag = 1;
		}
		else
		{
			ft_printf("Syntax Error\n"); 
			exit(-1); 
		}
	}
}
