/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiacovel <tiacovel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 10:37:05 by tiacovel          #+#    #+#             */
/*   Updated: 2024/03/22 12:44:14 by tiacovel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/commands.h"

int	input_heredoc(t_redirect *redirection)
{
	char	*line_read;
	int		fd;

	fd = open(TMP_FILENAME, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (red_error(FILE_NF));
	while (1)
	{
		line_read = readline("> ");
		if (!line_read || ft_strcmp(line_read, redirection->heredoc_delim) == 0)
		{
			if (line_read)
				free(line_read);
			break ;
		}
		write(fd, line_read, ft_strlen(line_read));
		write(fd, "\n", 1);
		free(line_read);
	}
	close(fd);
	redirection->file_name = ft_strdup(TMP_FILENAME);
	input_redirection(redirection);
	return (EXIT_SUCCESS);
}

int	input_redirection(t_redirect *redirection)
{
	int	fd;

	fd = open(redirection->file_name, O_RDONLY);
	if (fd == -1)
		return (red_error(FILE_NF));
	if (dup2(fd, STDIN_FILENO) == -1)
		return (red_error(RED_IN_ERR));
	close(fd);
	return (EXIT_SUCCESS);
}
