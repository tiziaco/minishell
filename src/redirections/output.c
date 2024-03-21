/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 10:37:05 by tiacovel          #+#    #+#             */
/*   Updated: 2024/03/20 20:26:57 by jkaller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/commands.h"

static int	check_file_name(char *file_name)
{
	int	i;

	if (file_name == NULL)
		return (0);
	if (file_name[0] == '\0')
		return (0);
	if (is_directory(file_name))
		return (0);
	return (1);
}

int	output_truncate(t_cmd *cmd)
{
	int	fd;

	if (check_file_name(cmd->redirections->file_name) == 0)
		return (red_error(INVALID_FNAME));
	fd = open(cmd->redirections->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	printf("file descriptor %d\n", fd);
	printf("file name %s\n", cmd->redirections->file_name);
	if (fd == -1)
		return (red_error(FILE_NF));
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (red_error(RED_OUT_ERR));
	close(fd);
	// Execute the command
	// After the execution of the command, restore the value of 
	// STDIN to the default one
	return (EXIT_SUCCESS);
}

int	output_append(t_cmd *cmd)
{
	int	fd;

	if (check_file_name(cmd->redirections->file_name) == 0)
		return (red_error(INVALID_FNAME));
	fd = open(cmd->redirections->file_name, O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (fd == -1)
		return (red_error(FILE_NF));
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (red_error(RED_OUT_ERR));
	close(fd);
	return (EXIT_SUCCESS);
}
