/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiacovel <tiacovel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 10:37:05 by tiacovel          #+#    #+#             */
/*   Updated: 2024/02/26 12:24:58 by tiacovel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/commands.h"

void	heredoc(char *delimeter)
{
	char	*line_read;
	int		fd;

	fd = open(TMP_FILENAME, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
	{
		perror("Failed to open file");
		return ;
	}
	line_read = readline("> ");
	while (ft_strcmp(line_read, delimeter))
	{
		write(fd, line_read, ft_strlen(line_read));
		write(fd, "\n", 1);
		free(line_read);
		line_read = readline("> ");
	}
	free(line_read);
	close(fd);
}

void	input_redirection(char *redirection, char *file_name)
{
	int	file_descriptor;

	if (ft_strcmp(redirection, "<") == 0)
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
	// Execute the command
	// After the execution of the command, restore the value of 
	// STDIN to the default one
}
