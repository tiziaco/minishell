/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_to_commands_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 20:28:01 by jkaller           #+#    #+#             */
/*   Updated: 2024/03/20 20:44:19 by jkaller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minish.h"
#include "../../../include/parser.h"
#include "../../../include/libft.h"
#include <unistd.h>

void    print_node(t_tree_node *tree)
{
	ft_printf("\n\n");
	printf("Leaf Header: %d\nGrammar Type: %d\nToken Value: %s\n",
		tree->leaf_header,
		tree->grammar_type,
		tree->token_value
	);
}

void	print_command_struct(t_cmd	*commands)
{
	ft_printf("\n");
	ft_printf("Command: %s\nArgs: %p\nIs Piped: %d\nRedirect: %d\nPipe FD: %p\nFilename: %s\nHeredoc Delim: %s\nPipe In: %d\nPipe Out: %d\nFD In: %d\nFD Out: %d\nNext: %p\nPrev: %p\n",
		(*commands).command,
		(*commands).args,
		(*commands).is_piped,
		(*commands).pipe_fd,
		(*commands).pipe_in,
		(*commands).pipe_out,
		(*commands).next,
		(*commands).prev);
}

void	print_command_args(char	**args)
{
	int	index;

	index = 0;
	ft_printf("\nArg List: \n");
	while (args[index])
	{
		ft_printf("arg[%i]: %s\n", index, args[index]);
		index++;
	}
}

void	print_command_redirections(t_redirect *current_node)
{
	ft_printf("\nRedirect List: \n");
	while (current_node)
	{
		ft_printf("redirect: %i\n", current_node->redirect);
		ft_printf("file_name: %s\n", current_node->file_name);
		ft_printf("heredoc_delim: %s\n", current_node->heredoc_delim);
		ft_printf("fd_in: %i\n", current_node->fd_in);
		ft_printf("fd_out: %i\n", current_node->fd_out);
		current_node = current_node->next;
		ft_printf("\n");
	}
}

void	print_entire_command_struct(t_cmd	*commands)
{
	// while (commands && commands->prev)
	// 	commands = commands->prev;
	ft_printf("\n");
	while (commands)
	{
		ft_printf("Command: %s\nArgs: %p\nIs Piped: %d\nRedirect: %p\nPipe FD: %p\nPipe In: %d\nPipe Out: %d\nNext: %p\nPrev: %p\n",
		(*commands).command,
		(*commands).args,
		(*commands).is_piped,
		(*commands).redirections,
		(*commands).pipe_fd,
		(*commands).pipe_in,
		(*commands).pipe_out,
		(*commands).next,
		(*commands).prev);
		if ((*commands).args != NULL)
			print_command_args((*commands).args);
		if (commands->redirections != NULL)
			print_command_redirections(commands->redirections);
		commands = commands->next;
		ft_printf("\n");
	}
}