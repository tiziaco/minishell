/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverse_algo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 15:03:02 by jkaller           #+#    #+#             */
/*   Updated: 2024/03/12 22:02:55 by jkaller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minish.h"
#include "../../../include/parser.h"
#include "../../../include/libft.h"
#include <unistd.h>
#include <stdio.h>

void	add_args(t_tree_node *tree_node, t_cmd *current_command, char **token_value)
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
	ft_printf("args added\n");
	//print_command_struct(current_command);
}

t_cmd *create_new_command(t_tree_node *tree_node, t_cmd *commands, char **token_value)
{
	t_cmd	*new_command;

	new_command = (t_cmd *)ft_calloc(sizeof(t_cmd), 1);
	if (*token_value != NULL)
    	new_command->command = ft_strdup(*token_value);
	new_command->argc = 0;
	new_command->args = (char **)ft_calloc(sizeof(char *), (new_command->argc + 2));
	ft_printf("new command created\n");
	if (*token_value != NULL)
	{
		add_args(tree_node, new_command, token_value);
   		free(*token_value);
		*token_value = NULL;
	}
    if (commands->command == NULL)
	{
        *commands = *new_command;
		//ft_printf("new command created\n");
    	//print_command_struct(new_command);
		return (commands);
	}
	else
        ft_cmdadd_back(&commands, new_command);
	//ft_printf("\nArg added! Complete struct below:");
    //print_command_struct(new_command);
    return (new_command);
}

void	add_file(t_tree_node *tree_node, t_cmd *current_command, char **filename)
{
	if (*filename == NULL)
		return ;
	if (!current_command->file_name)
		current_command->file_name = ft_strdup(*filename);
	free(*filename);
	*filename = NULL;
	ft_printf("file detected\n");
	//print_command_struct(current_command);
}

void	add_command(t_tree_node *tree_node, t_cmd *current_command, char **command_name)
{
	if (*command_name == NULL)
		return ;
	current_command->command = ft_strdup(*command_name);
	add_args(tree_node, current_command, command_name);
	free(*command_name);
	*command_name = NULL;
	ft_printf("command detected\n");
	//print_command_struct(current_command);
}

void	add_heredoc_delim(t_tree_node *tree_node, t_cmd *current_command, char **heredoc_delim)
{
	if (*heredoc_delim == NULL)
		return ;
	if (!current_command->heredoc_delim)
		current_command->heredoc_delim = ft_strdup(*heredoc_delim);
	free(*heredoc_delim);
	*heredoc_delim = NULL;
	ft_printf("heredoc delim detected\n");
	//print_command_struct(current_command);
}

void	check_node(t_tree_node *tree_node, t_cmd *commands)
{
	// static int			argc;
	static int			array_index = 0;
	static t_cmd		*current_command = NULL;
	static char 		*tmp_token_val = NULL;

	if (!current_command)
		current_command = create_new_command(tree_node, commands, &tmp_token_val);
	if (tree_node->grammar_type == WORD_TOKEN || tree_node->grammar_type == TREE_FILE || tree_node->grammar_type == TREE_LIMITER)
	{
		tmp_token_val = ft_strdup(tree_node->token_value);
		ft_printf("duplication occured");
	}
	else if (tree_node->leaf_header == CMD_NAME || tree_node->leaf_header == CMD_WORD)
	{
		if (current_command->command == NULL)
			add_command(tree_node, current_command, &tmp_token_val);
		else
			current_command = create_new_command(tree_node, commands, &tmp_token_val);
	}
	else if (tree_node->leaf_header == CMD_SUFFIX)
	{
		if (tmp_token_val != NULL)
			add_args(tree_node, current_command, &tmp_token_val);
	}
	else if (tree_node->grammar_type == PIPE_TOKEN)
	{
		current_command->is_piped = true;
		ft_printf("pipe added\n");
		//print_command_struct(current_command);
	}
	else if (tree_node->grammar_type >= REDIRECTION_INPUT_TOKEN && tree_node->grammar_type <= REDIRECTION_APPEND_TOKEN)
	{
		current_command->redirect = tree_node->grammar_type;
		ft_printf("redirection added\n");
		//print_command_struct(current_command);
	}
	else if (tree_node->leaf_header == FILENAME)
	{
		add_file(tree_node, current_command, &tmp_token_val);
		ft_printf("file added\n");
	}
	else if (tree_node->leaf_header == HERE_END)
		add_heredoc_delim(tree_node, current_command, &tmp_token_val);
	else if (tree_node->grammar_type == -2)
	{
		array_index = 0;
		free(tmp_token_val);
		tmp_token_val = NULL;
	}	
}	

void	fill_command_struct(t_tree_node *tree, t_cmd *command_stack)
{
	if (tree == NULL)  
		return ;
	fill_command_struct(tree->left, command_stack);
	fill_command_struct(tree->right, command_stack);
	print_node(tree);
	check_node(tree, command_stack);
}
