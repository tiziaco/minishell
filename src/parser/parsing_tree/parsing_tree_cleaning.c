/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tree_cleaning.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 12:08:54 by jkaller           #+#    #+#             */
/*   Updated: 2024/03/04 17:30:51 by jkaller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minish.h"
#include "../../../include/parser.h"
#include "../../../include/libft.h"
#include <unistd.h>

void	execute_type_changes(t_tree_node *node)
{
	if (!node)
		return ;
	if (node->leaf_header == FILENAME)
		node->right->grammar_type = TREE_FILE;
	if (node->leaf_header == HERE_END)
		node->right->grammar_type = TREE_LIMITER;
	if (node->leaf_header > CMD_WORD)
	{
		if (node->left && node->left->grammar_type == TREE_CMD)
			node->left->grammar_type = TREE_PARAM;
		if (node->right && node->right->grammar_type == TREE_CMD)
			node->right->grammar_type = TREE_PARAM;
	}
	execute_type_changes(node->left);
	execute_type_changes(node->right);
}

t_tree_node	*clarify_grammar_types(t_tree_node *parsing_tree)
{
	if (parsing_tree && parsing_tree->grammar_type == -1)
		parsing_tree->grammar_type = TREE_ROOT;
	execute_type_changes(parsing_tree);
	return (parsing_tree);
}