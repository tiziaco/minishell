/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiacovel <tiacovel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 10:37:05 by tiacovel          #+#    #+#             */
/*   Updated: 2024/02/23 13:33:28 by tiacovel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/commands.h"

static void	heredoc(char *delimeter, int *fd_here)
{
	char	*line_read;

	line_read = readline("> ");
	while (ft_strcmp(line_read, delimeter))
	{
		write(fd_here[1], line_read, ft_strlen(line_read));
		write(fd_here[1], "\n", 1);
		line_read = readline("> ");
	}
}

void	input_redirection(char *redirection, char *file_name)
{
	int	file_descriptor;

	if (ft_strcmp(redirection, "<") == 0)
		file_descriptor = open(file_name, O_RDONLY);
	else if (ft_strcmp(redirection, "<<") == 0)
		file_descriptor = open(file_name, O_RDONLY);
	if (file_descriptor == -1)
	{
		perror("Failed to open file");
		return ;
	}
	if (dup2(file_descriptor, STDIN_FILENO) == -1)
	{
		perror("Failed to redirect stdin");
		close(file_descriptor);
	}
	close(file_descriptor);
	// After the execution of the command, restore the value of 
	// STDIN to the default one
}
