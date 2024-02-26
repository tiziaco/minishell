/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tree_handler.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 17:23:40 by jkaller           #+#    #+#             */
/*   Updated: 2024/02/26 19:50:34 by jkaller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minish.h"
#include "../../../include/parsing.h"
#include "../../../include/libft.h"
#include <unistd.h>

void	check_grammar(int state, int grammar_type, t_table	*parsing_table)
{
	state = 0;
	grammar_type = 0;
	parsing_table = NULL;
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

t_token	*get_next_token(t_token *token_stack)
{
	static t_token	*next_token = NULL;
	t_token			*current_token;

	if (next_token == NULL)
		next_token = token_stack;
	current_token = next_token;
	next_token = next_token->next;
	return (current_token);
}

int	create_binary_tree(t_token *token_stack,
			t_table *parsing_table, t_tree_node **parsing_tree)
{
	t_token			*current_token;
	t_tree_stack	*tree_stack;

	tree_stack = (t_tree_stack *)malloc(sizeof(t_tree_stack));
	if (!tree_stack)
		return (-1);
	current_token = get_next_token(token_stack);
	//ft_printf("Token Type: %i\n", current_token->type);
	intialise_tree(*parsing_tree, tree_stack);
	while (current_token)
	{
		check_grammar(tree_stack->state, tree_stack->grammar_type, parsing_table);
		current_token = get_next_token(token_stack);
		break ;
	}
	free(tree_stack);
	return (0);
}

// t_token	*ft_lstnew_token(char *value, TokenTypes token_type)
// {
// 	t_token	*node;

// 	node = (t_token *)malloc(sizeof(t_token));
// 	node->value = 0;
// 	node->type = 0;
// 	if (!node)
// 		return (NULL);
// 	if (value == NULL)
// 		node->value = NULL;
// 	else
// 		node->value = ft_strdup(value);
// 	node->type = token_type;
// 	node->next = NULL;
// 	return (node);
// }