/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 17:48:07 by jkaller           #+#    #+#             */
/*   Updated: 2024/03/08 14:48:20 by jkaller          ###   ########.fr       */
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
		return (EXIT_FAILURE);
	if (tokenize_input(data->line, &token_stack) == EXIT_SUCCESS)
	{
		if (parse_table(PARSING_TABLE_PATH, parsing_table) == EXIT_SUCCESS)
		{
			abstract_syntax_tree = create_syntax_tree(token_stack, &parsing_table);
			//print_parsing_tree(abstract_syntax_tree, 0);
			if (abstract_syntax_tree != NULL)
			{
				data->cmd = add_to_command_struct(abstract_syntax_tree);
				//print_entire_command_struct(data->cmd);
				if (data->cmd != NULL)
				{
					//free_all(parsing_table, token_stack, abstract_syntax_tree);
					return (OP_SUCCESS); //TO BE CHANGED
				}
				else
					return (OP_FAIL); //TO BE CHANGED
			}
		}	
	}
	else
	{
		//free_token_stack(token_stack);
		return (OP_FAIL);
	}
	//free_command_struct(command_stack);
	return (OP_SUCCESS);
}
