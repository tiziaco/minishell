/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 17:48:07 by jkaller           #+#    #+#             */
/*   Updated: 2024/02/28 18:49:23 by jkaller          ###   ########.fr       */
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


int	parse_input(int argc, char *argv[])
{
	t_token		*token_stack;
	t_table		*parsing_table;
	t_tree_node	*parsing_tree;

	parsing_table = (t_table *)malloc(PARSING_TABLE_LENGTH * sizeof(t_table));
	if (!parsing_table)
		return (-1);
	parsing_tree = (t_tree_node *)malloc(sizeof(t_tree_node));
	if (!parsing_tree)
		return (-1);
	tokenize_input(argc, argv, &token_stack);
	parse_table(PARSING_TABLE_PATH, parsing_table);
	create_binary_tree(token_stack, &parsing_table, &parsing_tree);
	free(parsing_table);
	free(parsing_tree);
	free_token_stack(token_stack);
	return (0);
}
