/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_to_commands_main.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 12:37:20 by jkaller           #+#    #+#             */
/*   Updated: 2024/03/06 18:19:00 by jkaller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minish.h"
#include "../../../include/parser.h"
#include "../../../include/libft.h"
#include <unistd.h>

t_cmd	*init_cmd(void)
{
	t_cmd	*commmand_stack;

	commmand_stack = (t_cmd *)ft_calloc(sizeof(*commmand_stack), 1);
	if (!commmand_stack)
		exit(-1);
	commmand_stack->redirect = -1;
	return (commmand_stack);
}

t_cmd	*add_to_command_struct(t_tree_node *tree)
{
	t_cmd	*commmand_stack;
	
	commmand_stack = init_cmd();
	fill_command_struct(tree, commmand_stack);
	return(commmand_stack);
}