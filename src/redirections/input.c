/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiacovel <tiacovel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 10:37:05 by tiacovel          #+#    #+#             */
/*   Updated: 2024/03/06 17:01:07 by tiacovel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/commands.h"

int	input_heredoc(t_cmd *cmd)
{
	char	*line_read;
	int		fd;

	fd = open(TMP_FILENAME, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (red_error(FILE_NF));
	line_read = readline("> ");
	while (ft_strcmp(line_read, cmd->heredoc_delim))
	{
		write(fd, line_read, ft_strlen(line_read));
		write(fd, "\n", 1);
		free(line_read);
		line_read = readline("> ");
	}
	free(line_read);
	close(fd);
	return (EXIT_SUCCESS);
}

int	input_redirection(t_cmd *cmd)
{
	int	fd;

	fd = open(cmd->file_name, O_RDONLY);
	if (fd == -1)
		return (red_error(FILE_NF));
	if (dup2(fd, STDIN_FILENO) == -1)
		return (red_error(RED_IN_ERR));
	close(fd);
	// Execute the command
	// After the execution of the command, restore the value of 
	// STDIN to the default one
	return (EXIT_SUCCESS);
}
