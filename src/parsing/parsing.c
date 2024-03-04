/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 17:48:07 by jkaller           #+#    #+#             */
/*   Updated: 2024/03/04 13:15:11 by jkaller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minish.h"
#include "../../include/parsing.h"
#include "../../include/libft.h"
#include <unistd.h>

void	print_parsing_tree(t_tree_node *root, int depth)
{
	int	i;

	if (root == NULL)
		return ;
	i = 0;
	while (i < depth)
	{
		i++;
		ft_printf("  ");
	}
	ft_printf("%i: Leaf Header: %d, Grammar Type: %d, Token Value: %s\n",
		depth, root->leaf_header, root->grammar_type, root->token_value);
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
	free_all(parsing_table, token_stack, abstract_syntax_tree);
	return (0);
}
