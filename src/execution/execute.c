/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiacovel <tiacovel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 10:28:34 by tiacovel          #+#    #+#             */
/*   Updated: 2024/03/14 13:59:34 by tiacovel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/commands.h"
#include "../../include/minish.h"

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

static int	execute_in_child_process(t_data *data, t_cmd *current_cmd)
{
	int	status;

	data->pid = fork();
	if (data->pid == -1)
		return (sys_error(FORK_ERROR));
	else if (data->pid == 0)
	{
		/* printf("Child process executing command: %s\n", current_cmd->command);
		printf("Child process ID: %d\n", getpid()); */
		set_pipe_fds(data->cmd, current_cmd);
		if (is_path(current_cmd->command))
			status = exec_local_bin(data);
		else
			status = exec_bin(data);
		//exit(status);
	}
	return (EXIT_SUCCESS);
}

int	execute_command(t_data *data)
{
	int		status;
	char	*command_path;
	t_cmd	*current_cmd;

	init_pipes(data);
	//printf("Parent process ID: %d\n", getpid());
	current_cmd = data->cmd;
	while (current_cmd != NULL)
	{
		//set_pipe_fds(data->cmd, current_cmd);
		if (set_redirection(data, current_cmd) != EXIT_SUCCESS)
			current_cmd = current_cmd->next;
		if (current_cmd && is_builtin(current_cmd->command))
		{
			set_pipe_fds(data->cmd, current_cmd);
			status = exec_builtin(data);
		}
		else if (current_cmd)
			status = execute_in_child_process(data, current_cmd);
		//restore_std_io(data, current_cmd);
		if (current_cmd)
		{
			//status = waitpid(data->pid, NULL, 0);
			//wait_processes(data);
			current_cmd = current_cmd->next;
		}
	}
	wait_processes(data);
	free_command_struct(data->cmd);
	return (status);
}
