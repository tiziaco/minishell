/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sys_errors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiacovel <tiacovel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 16:48:07 by tiacovel          #+#    #+#             */
/*   Updated: 2024/02/28 14:20:28 by tiacovel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/commands.h"

int	sys_error(int err_code)
{
	if (err_code == MEM_ERROR)
		printf("Memorey allocation failed");
	else if (err_code == ARG_ERROR)
		printf("The arguments are invalid.");
	else if (err_code == CMD_ERROR)
		printf("Error while executing the command.");
	return (err_code);
}

int	cmd_error(int err_code)
{
	if (err_code == INVALID_KEY)
		printf("Invalid key name.");
	else if (err_code == ARG_ERROR)
		printf("The arguments are invalid.");
	else if (err_code == CMD_ERROR)
		printf("Error while executing the command.");
	return (err_code);
}