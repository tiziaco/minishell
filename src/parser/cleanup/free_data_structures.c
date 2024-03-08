/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data_structures.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiacovel <tiacovel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 12:32:57 by jkaller           #+#    #+#             */
/*   Updated: 2024/03/08 16:41:55 by tiacovel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minish.h"
#include "../../../include/parser.h"
#include "../../../include/libft.h"
#include <unistd.h>

void	free_token_stack(t_token *token_stack)
{
	t_token	*current;

	while (token_stack)
	{
		current = token_stack;
		token_stack = token_stack->next;
		free(current->value);
		free(current);
	}
}

void	free_stack(t_tree_stack *stack)
{
	t_tree_stack	*current_node;

	while (stack)
	{
		current_node = stack;
		stack = stack->next;
		free(current_node->token_value);
		free(current_node);
	}
}

void	free_syntax_tree(t_tree_node *root)
{
	if (root == NULL)
		return ;

	free_syntax_tree(root->left);
	free_syntax_tree(root->right);
	if (root->token_value)
		free(root->token_value);
	free(root);
}

void	free_args(char **args)
{
	int index;

	index = 0;
	while (args[index])
	{
		free(args[index]);
		args[index] = NULL;
		index++;
	}
	free(args);
	args = NULL;
}

void	free_command_struct(t_cmd *command_stack)
{
	t_cmd *current_node;
	
	
	while (command_stack)
	{
		current_node = command_stack;
		if (current_node->command)
			free(current_node->command);
		if (current_node->args)
			free_args(current_node->args);
		if (current_node->file_name)
			free(current_node->file_name);
		if (current_node->heredoc_delim)
			free(current_node->heredoc_delim);
		current_node = NULL;
		command_stack = command_stack->next;
		free(current_node);
	}
	free(command_stack);
}

void	free_all(t_table *parsing_table,
	t_token *token_stack, t_tree_node *abstract_syntax_tree)
{
	free(parsing_table);
	free_token_stack(token_stack);
	free_syntax_tree(abstract_syntax_tree);
}
