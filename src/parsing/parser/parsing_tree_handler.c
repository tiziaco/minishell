/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tree_handler.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 17:23:40 by jkaller           #+#    #+#             */
/*   Updated: 2024/02/27 16:26:40 by jkaller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minish.h"
#include "../../../include/parsing.h"
#include "../../../include/libft.h"
#include <unistd.h>

t_token	*get_next_token(t_token *token_stack)
{
	static t_token	*next_token = NULL;
	t_token			*current_token;

	if (next_token == NULL)
		next_token = token_stack;
	current_token = next_token;
	next_token = next_token->next;
	ft_printf("Token Type: %d\n", current_token->type);
	return (current_token);
}

void	intialise_tree(t_tree_node *tree_node, t_tree_stack *tree_stack)
{
	tree_node->grammar_type = 0;
	tree_node->token_value = NULL;
	tree_node->parent = NULL;
	tree_node->left = NULL;
	tree_node->right = NULL;

	tree_stack->grammar_type = 0;
	tree_stack->state = 0;
	tree_stack->next = NULL;
	tree_stack->previous = NULL;
}

int	create_binary_tree(t_token *token_stack,
			t_table *parsing_table, t_tree_node **parsing_tree)
{
	t_tree_stack	*tree_stack;

	tree_stack = (t_tree_stack *)malloc(sizeof(t_tree_stack));
	if (!tree_stack)
		return (-1);
	intialise_tree(*parsing_tree, tree_stack);
	parse_to_stack(token_stack, parsing_table, tree_stack);
	free(tree_stack);
	return (0);
}
