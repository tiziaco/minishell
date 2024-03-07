/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sys_errors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiacovel <tiacovel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 16:48:07 by tiacovel          #+#    #+#             */
/*   Updated: 2024/03/06 16:16:22 by tiacovel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/commands.h"

int	sys_error(int err_code)
{
	if (err_code == MEM_ERROR)
		printf("Memorey allocation failed\n");
	else if (err_code == ARG_ERROR)
		printf("The arguments are invalid.\n");
	else if (err_code == CMD_ERROR)
		printf("Error while executing the command.\n");
	else if (err_code == FORK_ERROR)
		printf("Error while forking parent process.\n");
	return (err_code);
}

int	cmd_error(int err_code)
{
	if (err_code == INVALID_KEY)
		printf("Invalid key name.\n");
	else if (err_code == ARG_ERROR)
		printf("The arguments are invalid.\n");
	else if (err_code == CMD_ERROR)
		printf("Error while executing the command.\n");
	else if (err_code == CMD_NOT_FOUND)
		printf("Command not found.\n");
	else if (err_code == CMD_NOT_EXEC)
		printf("Command not executable.\n");
	return (err_code);
}

int	red_error(int err_code)
{
	if (err_code == FILE_NF)
		printf("File not found.\n");
	else if (err_code == RED_IN_ERR)
		printf("Failed to redirect stdin.\n");
	else if (err_code == RED_OUT_ERR)
		printf("Failed to redirect stdout.\n");
	else if (err_code == INVALID_FNAME)
		printf("Invalid file name.\n");
	return (err_code);
}
