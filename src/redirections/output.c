/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiacovel <tiacovel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 10:37:05 by tiacovel          #+#    #+#             */
/*   Updated: 2024/02/23 12:33:08 by tiacovel         ###   ########.fr       */
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
	if (ft_strcmp(file_name, ".") == 0)
		return (0);
	return (1);
}

void	output_redirection(char *redirection, char *file_name)
{
	int	file_descriptor;

	if (check_file_name == 0)
	{
		perror("Invalid file name");
		return ;
	}
	if (ft_strcmp(redirection, ">") == 0)
		file_descriptor = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	else if (ft_strcmp(redirection, ">>") == 0)
		file_descriptor = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (file_descriptor == -1)
	{
		perror("Failed to open file");
		return ;
	}
	if (dup2(file_descriptor, STDOUT_FILENO) == -1)
	{
		perror("Failed to redirect stdout");
		close(file_descriptor);
	}
}
