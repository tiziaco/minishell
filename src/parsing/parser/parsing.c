/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 17:48:07 by jkaller           #+#    #+#             */
/*   Updated: 2024/02/23 18:46:17 by jkaller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minish.h"
#include "../../../include/parsing.h"
#include "../../../include/libft.h"
#include <unistd.h>

int	parse_input(int argc, char *argv[])
{
	//t_token	*token_stack;
	t_table	*parsing_table;

	argc = 0;
	argv = NULL;
	parsing_table = (t_table *)malloc(PARSING_TABLE_LENGTH * sizeof(t_table));
	if (!parsing_table)
        return (-1);
	//tokenize_input(argc, argv, &token_stack);
	parse_table("src/parsing/files/parsing_table.txt", &parsing_table);
	//free(parsing_table);
	return (0);
}
