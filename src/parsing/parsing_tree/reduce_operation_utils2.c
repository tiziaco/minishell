/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reduce_operation_utils2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 20:20:53 by jkaller           #+#    #+#             */
/*   Updated: 2024/03/02 17:44:26 by jkaller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minish.h"
#include "../../../include/parsing.h"
#include "../../../include/libft.h"
#include <unistd.h>

t_tree_node	*transform_stack_to_node(t_tree_stack *subtree)
{
	t_tree_node	*tree_node;

	tree_node = (t_tree_node *)malloc(sizeof(t_tree_node));
	if (tree_node)
	{
		//ft_printf("child added: grammar_type:%d, token_value: %s\n", tree_node->grammar_type, tree_node->token_value);
		tree_node->grammar_type = subtree->grammar_type;
		tree_node->leaf_header = -1;
		if (subtree->grammar_type >= 100)
		{
			tree_node->grammar_type = -1;
			tree_node->leaf_header = subtree->grammar_type;
		}
		tree_node->token_value = subtree->token_value;
		subtree->token_value = NULL;
		tree_node->left = NULL;
		tree_node->right = NULL;
		tree_node->next = NULL;
		//ft_printf("child added: grammar_type:%d, token_value: %s\n", tree_node->grammar_type, tree_node->token_value);
		return (tree_node);
	}
	return (NULL);
}

void	disconnect_subtree(t_tree_node **start_of_tree, t_tree_node *subtree_head)
{
	t_tree_node	*tmp;
	t_tree_node	*previous;

	if (*start_of_tree == subtree_head)
	{
		*start_of_tree = subtree_head->next;
		return ;
	}
	else
	{
		previous = NULL;
		tmp = *start_of_tree;
		while (tmp)
		{
			if (tmp == subtree_head)
			{
				previous->next = tmp->next;
				return ;
			}
			previous = tmp;
			tmp = tmp->next;
		}
	}
}

t_tree_node	*search_for_subtree(t_tree_node **parsing_tree, int reduced_token)
{
	t_tree_node *start_of_tree;
	t_tree_node	*subtree_head;

	subtree_head = NULL;
	start_of_tree = *parsing_tree;
	*parsing_tree = (*parsing_tree)->next;
	while (*parsing_tree)
	{
		if ((*parsing_tree)->leaf_header == reduced_token)
		{
			subtree_head = *parsing_tree;
			disconnect_subtree(&start_of_tree, *parsing_tree);
			break ;
		}
		*parsing_tree = (*parsing_tree)->next;
	}
	*parsing_tree = start_of_tree;
	return (subtree_head);
}
