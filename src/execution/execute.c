/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiacovel <tiacovel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 10:28:34 by tiacovel          #+#    #+#             */
/*   Updated: 2024/03/27 15:33:46 by tiacovel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/commands.h"
#include "../../include/minish.h"

static int	wait_processes(t_data *data)
{
	pid_t	wpid;
	int		status;
	int		save_status;

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

static void	execute_child_process(t_data *data, t_cmd *cmd)
{
	int	status;

	if (set_redirection(data, cmd) != EXIT_SUCCESS)
		exit(EXIT_FAILURE);
	set_pipe_fds(cmd);
	redirect_pipe_fds(cmd);
	if (is_builtin(cmd->command))
		status = exec_builtin(data, cmd);
	else if (is_path(cmd->command))
		status = exec_local_bin(data, cmd);
	else
		status = exec_bin(data, cmd);
	exit(status);
}

static int	execute_pipeline(t_data *data)
{
	t_cmd	*current_cmd;
	int		status;

	init_pipes(data);
	current_cmd = data->cmd;
	while (current_cmd != NULL)
	{
		data->pid = fork();
		if (data->pid == -1)
			return (sys_error(FORK_ERROR));
		else if (data->pid == 0)
			execute_child_process(data, current_cmd);
		close_pipe_fds(current_cmd);
		restore_std_io(data, current_cmd);
		current_cmd = current_cmd->next;
	}
	status = wait_processes(data);
	return (status);
}

int	execute_command(t_data *data)
{
	int	status;

	status = EXIT_FAILURE;
	if (data->cmd && is_builtin(data->cmd->command) 
		&& !data->cmd->is_piped)
	{
		if (set_redirection(data, data->cmd) == EXIT_SUCCESS)
			status = exec_builtin(data, data->cmd);
		restore_std_io(data, data->cmd);
	}
	else
		status = execute_pipeline(data);
	free_command_struct(data->cmd);
	return (status);
}
