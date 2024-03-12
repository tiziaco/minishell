/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_local_bin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiacovel <tiacovel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 12:38:26 by tiacovel          #+#    #+#             */
/*   Updated: 2024/03/11 17:27:59 by tiacovel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/commands.h"

int	check_command_path(t_cmd *cmd)
{
	if (access(cmd->command, F_OK) != 0)
		return (cmd_error(CMD_NOT_FOUND));
	else if (is_directory(cmd->command))
		return (cmd_error(CMD_NOT_FOUND));
	else if (access(cmd->command, F_OK | X_OK) != 0)
		return (cmd_error(CMD_NOT_EXEC));
	return (EXIT_SUCCESS);
}

bool	is_path(char *str)
{
	if (ft_strchr(str, '/') == NULL)
		return (false);
	return (true);
}

int	exec_local_bin(t_data *data)
{
	int	status;

	status = check_command_path(data->cmd);
	if (status != EXIT_SUCCESS)
		return (status);
	if (execve(data->cmd->command, data->cmd->args, data->envp))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
