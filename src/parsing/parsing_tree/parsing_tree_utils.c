/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tree_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 19:29:01 by jkaller           #+#    #+#             */
/*   Updated: 2024/03/02 18:28:18 by jkaller          ###   ########.fr       */
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

	if(!tree_stack)
		return (NULL);
	return_row = NULL;
	token_type = -1;
	if (token_stack)
		token_type = token_stack->type;
	//ft_printf("token_type: %d\n", token_type);
	current_row = parsing_table;
	row_index = 0;
	while (row_index <= PARSING_TABLE_LENGTH)
	{
		//ft_printf("%d Currently at: state%d, type: %d.  Looking for: state:%d, type:%d.\n", row_index, current_row->state, current_row->token_grammar_type, tree_stack->next_state, token_type);
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

t_tree_stack	*intialise_stack()
{
	t_tree_stack *start_of_stack;
	
	start_of_stack = (t_tree_stack *)malloc(sizeof(*start_of_stack));
	if (!start_of_stack)
		exit(-1);
	start_of_stack->token_value = NULL;
	start_of_stack->grammar_type = -1;
	start_of_stack->next_state = 0;
	start_of_stack->next = NULL;
	return (start_of_stack);
}
