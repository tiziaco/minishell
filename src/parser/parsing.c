/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 17:48:07 by jkaller           #+#    #+#             */
/*   Updated: 2024/03/07 20:06:52 by jkaller          ###   ########.fr       */
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
	//t_cmd		*command_stack;

	parsing_table = (t_table *)malloc(PARSING_TABLE_LENGTH * sizeof(t_table));
	if (!parsing_table)
		return (EXIT_FAILURE);
	tokenize_input(data->line, &token_stack);
	parse_table(PARSING_TABLE_PATH, parsing_table);
	abstract_syntax_tree = create_syntax_tree(token_stack, &parsing_table);
	//print_parsing_tree(abstract_syntax_tree, 0);
	data->cmd = add_to_command_struct(abstract_syntax_tree);
	//print_entire_command_struct(data->cmd);
	//free_all(parsing_table, token_stack, abstract_syntax_tree);
	//free_command_struct(command_stack);
	return (1);
}
