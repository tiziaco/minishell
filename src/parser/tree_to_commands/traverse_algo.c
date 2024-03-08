/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverse_algo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiacovel <tiacovel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 15:03:02 by jkaller           #+#    #+#             */
/*   Updated: 2024/03/08 16:44:33 by tiacovel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minish.h"
#include "../../../include/parser.h"
#include "../../../include/libft.h"
#include <unistd.h>
#include <stdio.h>

static int	argc_len(char **args)
{
	int	argc;

	argc = 0;

	while (args[argc] != NULL)
		argc++;
	return (argc);
}

void	add_args(t_tree_node *tree_node, t_cmd *current_command, char *token_value)
{
	static int	array_index = 0;
	int			argc;

	//argc = 0;
	if (!current_command->args)
	{
		current_command->args = (char **)ft_calloc(sizeof(char *), 2);
		//argc = argc_len(last_command->args);
	}
	(*current_command).args[array_index] = token_value;
	//print_command_args((*current_command).args);
	array_index++;
	token_value = NULL;
	//ft_printf("suffix detected and added");
	//print_command_struct(current_command);
}

t_cmd *create_new_command(t_tree_node *tree_node, t_cmd *commands, t_cmd *new_command, char *token_value)
{
	new_command = (t_cmd *)ft_calloc(sizeof(t_cmd), 1);
    new_command->command = ft_strdup(token_value);
	add_args(tree_node, new_command, ft_strdup(token_value));
	//new_command->args[0] = token_value;
    token_value = NULL;
    if (commands->command == NULL)
	{
        *commands = *new_command;
		//ft_printf("new command created\n");
    	//print_command_struct(new_command);
		return (commands);
	}
	else
        ft_cmdadd_back(&commands, new_command);
    //ft_printf("new command created\n");
    //print_command_struct(new_command);
    return (new_command);
}

void	add_file(t_tree_node *tree_node, t_cmd *current_command, char *filename)
{
	if (!current_command->file_name)
		current_command->file_name = (char *)malloc((ft_strlen(filename) + 1) * sizeof(char));
	(*current_command).file_name = filename;
	filename = NULL;
	//ft_printf("file detected\n");
	//print_command_struct(current_command);
}

void	add_heredoc_delim(t_tree_node *tree_node, t_cmd *current_command, char *heredoc_delim)
{
	if (!current_command->heredoc_delim)
		current_command->heredoc_delim = (char *)malloc((ft_strlen(heredoc_delim) + 1) * sizeof(char));
	(*current_command).heredoc_delim = heredoc_delim;
	heredoc_delim = NULL;
	//ft_printf("heredoc delim detected\n");
	//print_command_struct(current_command);
}

void	check_node(t_tree_node *tree_node, t_cmd *commands)
{
	// static int			argc;
	static t_cmd		*current_command = NULL;
	static char 		*tmp_token_val = NULL;

	if (tree_node->grammar_type == WORD_TOKEN || tree_node->grammar_type == TREE_FILE || tree_node->grammar_type == TREE_LIMITER)
	{
		tmp_token_val = ft_strdup(tree_node->token_value);
		//ft_printf("duplication occured");
	}
	if (tree_node->leaf_header == CMD_NAME)
	{
		current_command = create_new_command(tree_node, commands, current_command, tmp_token_val);
	}
	if (tree_node->leaf_header == CMD_SUFFIX)
	{
		if (tmp_token_val != NULL)
			add_args(tree_node, current_command, tmp_token_val);
	}
	if (tree_node->grammar_type == PIPE_TOKEN)
	{
		current_command->is_piped = true;
		//ft_printf("pipe detected\n");
		//print_command_struct(current_command);
	}
	if (tree_node->grammar_type >= REDIRECTION_INPUT_TOKEN && tree_node->grammar_type <= REDIRECTION_APPEND_TOKEN)
	{
		current_command->redirect = tree_node->grammar_type;
		//ft_printf("redirection detected\n");
		//print_command_struct(current_command);
	}
	if (tree_node->leaf_header == FILENAME)
		add_file(tree_node, current_command, tmp_token_val);
	if (tree_node->leaf_header == HERE_END)
		add_heredoc_delim(tree_node, current_command, tmp_token_val);
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
