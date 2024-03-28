/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data_structures.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiacovel <tiacovel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 12:32:57 by jkaller           #+#    #+#             */
/*   Updated: 2024/03/27 15:50:17 by tiacovel         ###   ########.fr       */
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
		index++;
	}
	free(args); //COMMENT: THIS USED TO BE AN ISSUE
}

void	free_redirections(t_redirect *current_node)
{
	t_redirect	*next_node;

	while (current_node)
	{
		next_node = current_node->next;
		if (current_node->file_name)
			free(current_node->file_name);
		if (current_node->heredoc_delim)
			free(current_node->heredoc_delim);
		free(current_node);
		current_node = next_node;
	}
}

void	free_command_struct(t_cmd *current_node)
{
	t_cmd	*next_node;

	while (current_node)
	{
		next_node = current_node->next;
		if (current_node->command)
			free(current_node->command);
		if (current_node->args)
			free_args(current_node->args);
		if (current_node->redirections)
			free_redirections(current_node->redirections);
		if (current_node->pipe_fd)
			free(current_node->pipe_fd);
		free(current_node);
		current_node = next_node;
	}
}

void	free_all(t_token *token_stack, t_tree_node *abstract_syntax_tree)
{
	free_syntax_tree(abstract_syntax_tree);
	free_token_stack(token_stack);
}
