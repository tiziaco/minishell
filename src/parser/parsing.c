/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 17:48:07 by jkaller           #+#    #+#             */
/*   Updated: 2024/03/04 18:27:36 by jkaller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minish.h"
#include "../../include/parser.h"
#include "../../include/libft.h"
#include <unistd.h>

int	parse_input(t_data *data)
{
	t_token		*token_stack;
	t_table		*parsing_table;
	t_tree_node	*abstract_syntax_tree;

	parsing_table = (t_table *)malloc(PARSING_TABLE_LENGTH * sizeof(t_table));
	if (!parsing_table)
		return (-1);
	tokenize_input(data->line, &token_stack);
	parse_table(PARSING_TABLE_PATH, parsing_table);
	abstract_syntax_tree = create_syntax_tree(token_stack, &parsing_table);
	//add_to_command_struct();
	print_parsing_tree(abstract_syntax_tree, 0);
	free_all(parsing_table, token_stack, abstract_syntax_tree);
	return (1);
}
