/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 17:48:07 by jkaller           #+#    #+#             */
/*   Updated: 2024/03/02 21:48:44 by jkaller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minish.h"
#include "../../include/parsing.h"
#include "../../include/libft.h"
#include <unistd.h>

void	free_table(t_table *parsing_table)
{
	while (parsing_table != NULL)
	{
		free(parsing_table);
		parsing_table++;
	}
	free(parsing_table);
}

// void	print_parsing_tree(t_tree_node *node)
// {
// 	static int count = 0;
// 	if (!node)
// 		return ;
// 	count++;
// 	ft_printf("%i:Node Info - leaf_header: %d, grammar_type: %d, token_value: %s\n",
// 		count, node->leaf_header, node->grammar_type, node->token_value);
// 	if (node->left)
// 	{
// 		//ft_printf("Going left\n");
// 		//sleep(1);
// 		print_parsing_tree(node->left);
// 	}
// 	if (node->right)
// 	{
// 		//ft_printf("Going right\n");
// 		//sleep(1);
// 		print_parsing_tree(node->right);
// 	}
// 	if (node->next)
// 	{
// 		//ft_printf("Going next\n");
// 		//sleep(1);
// 		print_parsing_tree(node->next);
// 	}
// }

void print_parsing_tree(t_tree_node *root, int depth)
{
    if (root == NULL) {
        return;
    }

    // Print the current node
    for (int i = 0; i < depth; i++) {
        ft_printf("  "); // Adjust spacing for better visualization
    }
    ft_printf("%i: Leaf Header: %d, Grammar Type: %d, Token Value: %s\n",
           depth, root->leaf_header, root->grammar_type, root->token_value);

    // Recursively print the left and right subtrees
    print_parsing_tree(root->left, depth + 1);
    print_parsing_tree(root->right, depth + 1);
}

int	parse_input(int argc, char *argv[])
{
	t_token		*token_stack;
	t_table		*parsing_table;
	t_tree_node	*abstract_syntax_tree;

	parsing_table = (t_table *)malloc(PARSING_TABLE_LENGTH * sizeof(t_table));
	if (!parsing_table)
		return (-1);
	tokenize_input(argc, argv, &token_stack);
	parse_table(PARSING_TABLE_PATH, parsing_table);
	abstract_syntax_tree = create_syntax_tree(token_stack, &parsing_table);
	print_parsing_tree(abstract_syntax_tree, 0);
	free(parsing_table);
	free(abstract_syntax_tree);
	free_token_stack(token_stack);
	return (0);
}
