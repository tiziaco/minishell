/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverse_algo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiacovel <tiacovel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 15:03:02 by jkaller           #+#    #+#             */
/*   Updated: 2024/03/22 11:36:07 by tiacovel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minish.h"
#include "../../../include/parser.h"
#include "../../../include/libft.h"
#include <unistd.h>
#include <stdio.h>

t_redirect	*find_last_node(t_redirect *last_node)
{
	while (last_node->next)
		last_node = last_node->next;
	return (last_node);
}

void	add_args(t_cmd *current_command, char **token_value)
{
	char **tmp_args;
	
	if (*token_value == NULL)
		return ;
	tmp_args = current_command->args;
	current_command->args = copy_environment(current_command->args, current_command->argc + 2);
	free_double_pointer(tmp_args);
	current_command->args[current_command->argc] = ft_strdup(*token_value);
	current_command->argc++;
	current_command->args[current_command->argc] = NULL;
	//print_command_args(current_command->args);
	free(*token_value);
	*token_value = NULL;
	//ft_printf("args added\n");
	//print_command_struct(current_command);
}

t_cmd *create_new_command(t_cmd *commands, char **token_value)
{
	t_cmd	*new_command;

	new_command = (t_cmd *)ft_calloc(sizeof(t_cmd), 1);
	//ft_printf("new command created");
	if (!new_command)
		return (NULL);
	if (*token_value != NULL)
    	new_command->command = ft_strdup(*token_value);
	new_command->args = (char **)ft_calloc(sizeof(char *), (new_command->argc + 1));
	new_command->pipe_in = 0;
	new_command->pipe_out = 1;
	if (*token_value != NULL)
	{
		add_args(new_command, token_value);
   		free(*token_value);
		*token_value = NULL;
	}
	if (commands->command == NULL)
	{
        *commands = *new_command;
		free(new_command);
		return (commands);
	}
	else
	{
		ft_cmdadd_back(&commands, new_command);
		return (new_command);
	}
}

void	add_file(t_cmd *current_command, char **filename)
{
	t_redirect	*last_node;

	last_node = find_last_node(current_command->redirections);
	if (last_node == NULL)
		return ;
	if (!last_node->file_name)
		last_node->file_name = ft_strdup(*filename);
	free(*filename);
	*filename = NULL;
	//ft_printf("file detected\n");
	//print_command_struct(current_command);
}

void	add_command(t_cmd *current_command, char **command_name)
{
	if (*command_name == NULL)
		return ;
	current_command->command = ft_strdup(*command_name);
	add_args(current_command, command_name);
	free(*command_name);
	*command_name = NULL;
	//ft_printf("command detected\n");
	//print_command_struct(current_command);
}

void	add_heredoc_delim(t_cmd *current_command, char **heredoc_delim)
{
	t_redirect	*last_node;

	last_node = find_last_node(current_command->redirections);
	if (last_node == NULL)
		return ;
	if (!last_node->heredoc_delim)
		last_node->heredoc_delim = ft_strdup(*heredoc_delim);
	free(*heredoc_delim);
	*heredoc_delim = NULL;
	//ft_printf("heredoc delim detected\n");
	//print_command_struct(current_command);
}

void	add_redirect(int redirect, t_cmd *current_command)
{
	t_redirect	*new_node;

	new_node = ft_lstnew_redirect(redirect);
	if (new_node == NULL)
		return ;
	ft_redirectadd_back(&current_command->redirections, new_node);
	//ft_printf("redirect detected: %i\n", redirect);
	//print_command_struct(current_command);
}

void	check_node(t_tree_node *tree_node, t_cmd *commands)
{
	static t_cmd		*current_command = NULL;
	static char 		*tmp_token_val = NULL;

	if (!current_command)
		current_command = create_new_command(commands, &tmp_token_val);
	if (tree_node->grammar_type == WORD_TOKEN || tree_node->grammar_type == TREE_FILE || tree_node->grammar_type == TREE_LIMITER)
	{
		tmp_token_val = ft_strdup(tree_node->token_value);
		//ft_printf("duplication occured");
	}
	else if (tree_node->leaf_header == CMD_NAME || tree_node->leaf_header == CMD_WORD)
	{
		if (current_command->command == NULL)
			add_command(current_command, &tmp_token_val);
		else
			current_command = create_new_command(commands, &tmp_token_val);
	}
	else if (tree_node->leaf_header == CMD_SUFFIX || tree_node->leaf_header == CMD_PREFIX)
	{
		if (tmp_token_val != NULL)
			add_args(current_command, &tmp_token_val);
	}
	else if (tree_node->grammar_type == PIPE_TOKEN)
	{
		current_command->is_piped = true;
		//ft_printf("pipe added\n");
		//print_command_struct(current_command);
	}
	else if (tree_node->grammar_type >= INPUT_TOKEN && tree_node->grammar_type <= APPEND_TOKEN)
	{
		add_redirect(tree_node->grammar_type, current_command);
		//ft_printf("redirection added\n");
		//print_command_struct(current_command);
	}
	else if (tree_node->leaf_header == FILENAME)
	{
		add_file(current_command, &tmp_token_val);
		//ft_printf("file added\n");
	}
	else if (tree_node->leaf_header == HERE_END)
		add_heredoc_delim(current_command, &tmp_token_val);
	else if (tree_node->grammar_type == -2)
	{
		free(tmp_token_val);
		tmp_token_val = NULL;
		current_command = NULL;
	}
}

void	fill_command_struct(t_tree_node *tree, t_cmd *command_stack)
{
	if (tree == NULL)  
		return ;
	fill_command_struct(tree->left, command_stack);
	fill_command_struct(tree->right, command_stack);
	//print_node(tree);
	check_node(tree, command_stack);
}
