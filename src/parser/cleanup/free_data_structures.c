/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data_structures.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 12:32:57 by jkaller           #+#    #+#             */
/*   Updated: 2024/03/04 17:30:35 by jkaller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minish.h"
#include "../../../include/parser.h"
#include "../../../include/libft.h"
#include <unistd.h>

void	free_token_stack(t_token *token_stack)
{
	t_token	*current;

	while (token_stack)
	{
		current = token_stack;
		token_stack = token_stack->next;
		free(current->value);
		free(current);
	}
}

void	free_stack(t_tree_stack *stack)
{
	t_tree_stack	*current_node;

	while (stack)
	{
		current_node = stack;
		stack = stack->next;
		free(current_node->token_value);
		free(current_node);
	}
}

void	free_syntax_tree(t_tree_node *root)
{
	if (root == NULL)
		return ;

	free_syntax_tree(root->left);
	free_syntax_tree(root->right);
	if (root->token_value)
		free(root->token_value);
	free(root);
}

void	free_all(t_table *parsing_table,
	t_token *token_stack, t_tree_node *abstract_syntax_tree)
{
	free(parsing_table);
	free_token_stack(token_stack);
	free_syntax_tree(abstract_syntax_tree);
}
