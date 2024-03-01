/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiacovel <tiacovel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 09:21:59 by tiacovel          #+#    #+#             */
/*   Updated: 2024/03/01 12:38:28 by tiacovel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/commands.h"

bool	is_builtin(char *arg)
{
	if (!arg)
		return (false);
	if (!ft_strcmp(arg, "echo")
		|| !ft_strcmp(arg, "cd")
		|| !ft_strcmp(arg, "exit")
		|| !ft_strcmp(arg, "pwd")
		|| !ft_strcmp(arg, "export")
		|| !ft_strcmp(arg, "unset")
		|| !ft_strcmp(arg, "env"))
		return (true);
	return (false);
}

int	exec_builtin(t_data *data)
{
	if (ft_strcmp(data->cmd->command, "echo") == 0)
		return (ft_echo(data->cmd->args));
	if (ft_strcmp(data->cmd->command, "cd") == 0)
		return (ft_cd(data->cmd->args[1]));
	if (ft_strcmp(data->cmd->command, "env") == 0)
		return (ft_env(data->envp));
	if (ft_strcmp(data->cmd->command, "pwd") == 0)
		return (ft_pwd());
	if (ft_strcmp(data->cmd->command, "export") == 0)
		return (ft_export(data, data->cmd->args));
	if (ft_strcmp(data->cmd->command, "unset") == 0)
		return (ft_unset(data, data->cmd->args));
	return (OP_FAIL);
}
