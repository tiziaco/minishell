/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tree_grammar.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:02:40 by jkaller           #+#    #+#             */
/*   Updated: 2024/02/27 17:58:16 by jkaller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minish.h"
#include "../../../include/parsing.h"
#include "../../../include/libft.h"
#include <unistd.h>

int	get_next_action(t_table	*parsing_table, int current_state, int current_type)
{
	t_table *current_row;
	int	row_index;

	current_row = parsing_table;
	row_index = 0;
	while (row_index <= PARSING_TABLE_LENGTH)
	{
		if (current_row->state == current_state && (current_row->token_grammar_type == current_type || current_row->token_grammar_type == -1)) 
			return (current_row->action);
		//ft_printf("DEBUG: state=%d, token type=%d\n", current_row->state, current_row->token_grammar_type);
		row_index++;
		current_row++;
	}
	return (-1);
}

int	perform_reduce(t_tree_stack **tree_stack, t_table *parsing_table, int current_state, t_token *current_token)
{
	t_table	*current_row;
	int		row_index;

	current_row = parsing_table;
	row_index = 0;
	while (row_index <= PARSING_TABLE_LENGTH)
	{
		if (current_row->state == current_state && (current_row->token_grammar_type == current_token->type || current_row->token_grammar_type == -1))
		{
			(*tree_stack)->state = current_row->next_state;
			(*tree_stack)->grammar_type = current_row->reduced_token;
			return (1);
		}
		current_row++;
		row_index++;
	}
	return (0);
}

void	perform_shift(t_tree_stack **tree_stack, t_table *parsing_table,
	int current_state, t_token *current_token)
{
	t_tree_stack	*new_tree_stack;
	t_table			*start_of_table;
	int				next_state;
	int				row_index;

	new_tree_stack = (t_tree_stack *)malloc(sizeof(t_tree_stack));
	start_of_table = parsing_table;
	next_state = -1;
	row_index = 0;
	while (row_index <= PARSING_TABLE_LENGTH)
	{
		if (parsing_table->state == current_state
			&& parsing_table->token_grammar_type == current_token->type)
		{
			next_state = parsing_table->next_state;
			break ;
		}
		parsing_table++;
		row_index++;
	}
	parsing_table = start_of_table;
	new_tree_stack->state = next_state;
	new_tree_stack->grammar_type = current_token->type;
	new_tree_stack->token_value = ft_strdup(current_token->value);
	new_tree_stack->next = (struct t_tree_stack *)*tree_stack;
	*tree_stack = new_tree_stack;
}

void	parse_to_stack(t_token *token_stack,
			t_table *parsing_table, t_tree_stack *tree_stack) //I want to run this function after every get_next_token or reduce
{
	int		action;
	int		process_done_flag;
	t_token	*current_token;

	process_done_flag = 0;
	current_token = get_next_token(token_stack);
	while (process_done_flag == 0)
	{
		action = get_next_row(parsing_table, tree_stack->state, current_token->type);
		ft_printf("DEBUG: state=%d, token type=%d, action=%d\n", tree_stack->state, current_token->type, action);
		if (action == SHIFT)
		{
			perform_shift(&tree_stack, parsing_table, tree_stack->state, current_token);
			current_token = get_next_token(token_stack);
		}
		else if (action == REDUCE)
			perform_reduce(&tree_stack, parsing_table, tree_stack->state, current_token);
		else if (action == ACCEPT)
			process_done_flag = 1;
		else
		{
			ft_printf("Syntax Error\n"); 
			exit(-1); 
		}
	}
}
