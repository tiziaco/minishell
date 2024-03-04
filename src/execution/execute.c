/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiacovel <tiacovel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 10:28:34 by tiacovel          #+#    #+#             */
/*   Updated: 2024/03/04 15:06:35 by tiacovel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/commands.h"

static int	execute_in_child_process(t_data *data)
{
	t_cmd	*cmd;

	cmd = data->cmd;
	while (data->pid != 0 && cmd)
	{
		data->pid = fork();
		if (data->pid == -1)
			return (sys_error(FORK_ERROR));
		else if (data->pid == 0)
			execute_command(data);
		cmd = cmd->next;
	}
	return (wait_processes(data));
}

static int	wait_processes(t_data *data)
{
	pid_t	wpid;
	int		status;
	int		save_status;

	// close_fds(data->cmd, false);
	save_status = 0;
	wpid = 0;
	while (wpid != -1)
	{
		wpid = waitpid(-1, &status, 0);
		if (wpid == data->pid)
			save_status = status;
		continue ;
	}
	if (WIFSIGNALED(save_status))
		status = 128 + WTERMSIG(save_status);
	else if (WIFEXITED(save_status))
		status = WEXITSTATUS(save_status);
	else
		status = save_status;
	return (status);
}

int	execute_command(t_data *data)
{
	char	*command_path;

	if (is_builtin(data->cmd->command))
		exec_builtin(data);
	else if (is_path(data->cmd->command))
		exec_local_bin(data);
	else
		exec_bin(data);
	return (OP_SUCCESS);
}
