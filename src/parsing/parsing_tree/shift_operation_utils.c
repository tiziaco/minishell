/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shift_operation_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 19:28:29 by jkaller           #+#    #+#             */
/*   Updated: 2024/03/02 20:21:48 by jkaller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minish.h"
#include "../../../include/parsing.h"
#include "../../../include/libft.h"
#include <unistd.h>

void	push_token_to_stack(t_tree_stack **tree_stack, t_token *token_stack)
{
	t_tree_stack	*new_tree_stack;
	
	//ft_printf("token to be shifted: %d, %s.\n", token_stack->type, token_stack->value);
	new_tree_stack = (t_tree_stack *)malloc(sizeof(t_tree_stack));
	new_tree_stack->grammar_type = token_stack->type;
	new_tree_stack->next_state = -1;
	new_tree_stack->token_value = token_stack->value;
    token_stack->value = NULL;
	new_tree_stack->next = *tree_stack;
	*tree_stack = new_tree_stack;
}

int	push_state_to_stack(t_tree_stack **tree_stack, int next_state)
{
	t_tree_stack	*new_tree_stack;

	if (next_state == -1)
		return (-1);
	new_tree_stack = (t_tree_stack *)malloc(sizeof(t_tree_stack));
	new_tree_stack->grammar_type = -1;
	new_tree_stack->next_state = next_state;
	new_tree_stack->token_value = NULL;
	new_tree_stack->next = *tree_stack;
	*tree_stack = new_tree_stack;
	return (0);
}
