/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiacovel <tiacovel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 09:21:59 by tiacovel          #+#    #+#             */
/*   Updated: 2024/03/21 16:50:15 by tiacovel         ###   ########.fr       */
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

int	exec_builtin(t_data *data, t_cmd *cmd)
{
	if (ft_strcmp(cmd->command, "echo") == 0)
		return (ft_echo(cmd->args));
	if (ft_strcmp(cmd->command, "cd") == 0)
		return (ft_cd(cmd->args[1]));
	if (ft_strcmp(cmd->command, "env") == 0)
		return (ft_env(data->envp));
	if (ft_strcmp(cmd->command, "pwd") == 0)
		return (ft_pwd());
	if (ft_strcmp(cmd->command, "export") == 0)
		return (ft_export(data, cmd->args));
	if (ft_strcmp(cmd->command, "unset") == 0)
		return (ft_unset(data, cmd->args));
	return (OP_FAIL);
}
