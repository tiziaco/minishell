/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reduce_operation_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 19:28:12 by jkaller           #+#    #+#             */
/*   Updated: 2024/03/02 21:24:33 by jkaller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minish.h"
#include "../../../include/parsing.h"
#include "../../../include/libft.h"
#include <unistd.h>

int	add_reduction_node(t_tree_stack **tree_stack, int reduction_token)
{
	t_tree_stack	*reduction_node;

	reduction_node = (t_tree_stack *)malloc(sizeof(t_tree_stack));
	if (reduction_node == NULL)
		return (-1);
	reduction_node->grammar_type = reduction_token;
	reduction_node->next_state = -1;
	reduction_node->token_value = NULL;
	reduction_node->next = *tree_stack;
	*tree_stack = reduction_node;
	return (0);
}

t_tree_stack	*create_subtree(t_tree_stack **tree_stack, int tokens_to_reduce)
{
	int				count;
	t_tree_stack	*next;
	t_tree_stack	*subtree;

	subtree = NULL;
	if (tree_stack)
	{
		count = 0;
		while (count < tokens_to_reduce)
		{
			//ft_printf("token reduced: %i\n", count);
			next = (*tree_stack)->next;
			free(*tree_stack);
			*tree_stack = next;
			next = (*tree_stack)->next;
			subtree_add_back(&subtree, *tree_stack);
			*tree_stack = next;
			count++;
		}
	}
	return (subtree);
}

t_tree_node *add_leaf_header(t_tree_node **parsing_tree, int reduced_token)
{
	t_tree_node *leaf_header;

	leaf_header = (t_tree_node *)malloc(sizeof(t_tree_node));
	if (leaf_header)
	{
		leaf_header->grammar_type = -1;
		leaf_header->token_value = NULL;
		leaf_header->leaf_header = reduced_token;
		leaf_header->left = NULL;
		leaf_header->right = NULL;
		leaf_header->next = *parsing_tree;
		*parsing_tree = leaf_header;
		//ft_printf("Leaf header to be added: leaf header val:%d, type:%d, token value: %s.\n", leaf_header->leaf_header, leaf_header->grammar_type, leaf_header->token_value);
		return (leaf_header);
	}
	return (NULL);
}

int	add_children(t_tree_node **parsing_tree, t_tree_node *leaf_header, t_tree_stack **subtree)
{
	t_tree_node		*child;
	t_tree_stack	*start_of_subtree;
	int				child_added_flag;

	start_of_subtree = *subtree;
	child_added_flag = -1;
	while (*subtree)
	{
		//ft_printf("\nsubtree loop\n");
		if ((*subtree)->grammar_type >= 100)
			child = search_for_subtree(parsing_tree, (*subtree)->grammar_type);
		else
			child = transform_stack_to_node(*subtree);
		//ft_printf("child to be added: type:%d, leaf_header/reduced:%d, token_value:%s\n", child->grammar_type, child->leaf_header, child->token_value);
		if (!child)
			return (-1);
		if (++child_added_flag == 0)
		{
			//(*parsing_tree)->right = child;
			leaf_header->right = child;
			//ft_printf("child added on the right: type:%d, leaf_header/reduced:%d, token_value:%s\n", (*parsing_tree)->right->grammar_type, (*parsing_tree)->right->leaf_header, (*parsing_tree)->right->token_value);
		}
		else
		{
			//(*parsing_tree)->left = child;
			leaf_header->left = child;
			//ft_printf("child added on the right: type:%d, leaf_header/reduced:%d, token_value:%s\n", (*parsing_tree)->left->grammar_type, (*parsing_tree)->left->leaf_header, (*parsing_tree)->left->token_value);
		}
		//print_parsing_tree(*parsing_tree, 0);
		if (child_added_flag == 1 && (*subtree)->next)
			leaf_header = leaf_header->left;
		(*subtree) = (*subtree)->next;
	}
	*subtree = start_of_subtree;
	return (0);
}

int	add_subtree_to_tree(t_tree_node **parsing_tree, t_tree_stack **subtree, int reduced_token)
{
	t_tree_node	*leaf_header;

	leaf_header = add_leaf_header(parsing_tree, reduced_token);
	//ft_printf("Leaf header to be added: leaf header val:%d, type:%d, token value: %s.\n", leaf_header->leaf_header, leaf_header->grammar_type, leaf_header->token_value);
	if (leaf_header)
	{
		if (!add_children(parsing_tree, leaf_header, subtree))
			return (0);
	}
	return (-1);
}
