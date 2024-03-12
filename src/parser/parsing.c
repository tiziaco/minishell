/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 17:48:07 by jkaller           #+#    #+#             */
/*   Updated: 2024/03/12 13:54:03 by jkaller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minish.h"
#include "../../include/parser.h"
#include "../../include/libft.h"
#include <unistd.h>

int	parse_input(t_data *data)
{
	t_token		*token_stack;
	t_tree_node	*abstract_syntax_tree;

	if (tokenize_input(data->line, &token_stack) == EXIT_SUCCESS)
	{
		abstract_syntax_tree = create_syntax_tree(token_stack, &data->parsing_table, data->table_length);
		print_parsing_tree(abstract_syntax_tree, 0);
		if (abstract_syntax_tree != NULL)
		{
			data->cmd = add_to_command_struct(abstract_syntax_tree);
			print_entire_command_struct(data->cmd);
			if (data->cmd != NULL)
			{
				//free_all(parsing_table, token_stack, abstract_syntax_tree);
				return (OP_SUCCESS); //TO BE CHANGED
			}
			else
				return (OP_FAIL); //TO BE CHANGED
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
