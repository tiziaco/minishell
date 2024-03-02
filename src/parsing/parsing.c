/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 17:48:07 by jkaller           #+#    #+#             */
/*   Updated: 2024/03/02 01:06:58 by jkaller          ###   ########.fr       */
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

void	print_parsing_tree(t_tree_node *node)
{
	if (!node)
		return ;
	ft_printf("Node Info - leaf_header: %d, grammar_type: %d, token_value: %s\n",
		node->leaf_header, node->grammar_type, node->token_value);
	if (node->left)
	{
		ft_printf("Going left\n");
		//sleep(1);
		print_parsing_tree(node->left);
	}
	if (node->right)
	{
		ft_printf("Going right\n");
		//sleep(1);
		print_parsing_tree(node->right);
	}
	if (node->next)
	{
		ft_printf("Going next\n");
		//sleep(1);
		print_parsing_tree(node->next);
	}
}

int	parse_input(int argc, char *argv[])
{
	t_token		*token_stack;
	t_table		*parsing_table;
	t_tree_node	*parsing_tree;

	parsing_table = (t_table *)malloc(PARSING_TABLE_LENGTH * sizeof(t_table));
	if (!parsing_table)
		return (-1);
	// parsing_tree = (t_tree_node *)malloc(sizeof(t_tree_node));
	// if (!parsing_tree)
	// 	return (-1);
	// parsing_tree->left = NULL;
    // parsing_tree->right = NULL;
    // parsing_tree->next = NULL;
    // parsing_tree->leaf_header = -1;
    // parsing_tree->grammar_type = -40;
    // parsing_tree->token_value = NULL;
	tokenize_input(argc, argv, &token_stack);
	parse_table(PARSING_TABLE_PATH, parsing_table);
	parsing_tree = create_binary_tree(token_stack, &parsing_table);
	//specify_params(&parsing_tree);
	print_parsing_tree(parsing_tree);
	free(parsing_table);
	free(parsing_tree);
	free_token_stack(token_stack);
	return (0);
}
