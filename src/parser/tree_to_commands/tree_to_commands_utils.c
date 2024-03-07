/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_to_commands_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 20:28:01 by jkaller           #+#    #+#             */
/*   Updated: 2024/03/07 15:52:09 by jkaller          ###   ########.fr       */
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
		(*commands).redirect,
		(*commands).pipe_fd,
		(*commands).filename,
		(*commands).heredoc_delim,
		(*commands).pipe_in,
		(*commands).pipe_out,
		(*commands).fd_in,
		(*commands).fd_out,
		(*commands).next,
		(*commands).prev);
}

void	print_entire_command_struct(t_cmd	*commands)
{
	// while (commands && commands->prev)
	// 	commands = commands->prev;
	ft_printf("\n");
	while (commands)
	{
		ft_printf("Command: %s\nArgs: %p\nIs Piped: %d\nRedirect: %d\nPipe FD: %p\nFilename: %s\nHeredoc Delim: %s\nPipe In: %d\nPipe Out: %d\nFD In: %d\nFD Out: %d\nNext: %p\nPrev: %p\n",
		(*commands).command,
		(*commands).args,
		(*commands).is_piped,
		(*commands).redirect,
		(*commands).pipe_fd,
		(*commands).filename,
		(*commands).heredoc_delim,
		(*commands).pipe_in,
		(*commands).pipe_out,
		(*commands).fd_in,
		(*commands).fd_out,
		(*commands).next,
		(*commands).prev);
		commands = commands->next;
		ft_printf("\n");
	}
}

void	print_command_args(char	**args)
{
	int	index;

	ft_printf("\n\n");
	index = 0;
	while (args[index] != NULL)
	{
		ft_printf("arg command: %s\n", args[index]);
		index++;
	}
}