/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiacovel <tiacovel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:27:23 by tiacovel          #+#    #+#             */
/*   Updated: 2024/03/27 15:57:29 by tiacovel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/commands.h"

int	init_pipes(t_data *data)
{
	int			*fd;
	t_cmd		*tmp;

	tmp = data->cmd;
	while (tmp)
	{
		if (tmp->is_piped)
		{
			fd = malloc(sizeof * fd * 2);
			if (!fd || pipe(fd) != 0)
			{
				free_data(data, false);
				return (EXIT_FAILURE);
			}
			tmp->pipe_fd = fd;
		}
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}

/* set_pipe_fds:
*	Sets the pipe fds for this command. If the previous command
*	was piped to this one, sets the input as the read end of
*	the previous command. If this command is piped to the
*	next, sets the output ad the write end of the pipe.
*		pipe_fd[0] = read end of pipe.
*		pipe_fd[1] = write end of pipe.
*	Returns true when the pipe file descriptors are set.
*/
int	set_pipe_fds(t_cmd *cmd)
{
	if (!cmd)
		return (EXIT_FAILURE);
	if (cmd->is_piped && cmd->prev == NULL)
	{
		cmd->pipe_in = 0;
		cmd->pipe_out = cmd->pipe_fd[1];
	}
	else if (cmd->is_piped && cmd->prev->is_piped)
	{
		cmd->pipe_in = cmd->prev->pipe_fd[0];
		cmd->pipe_out = cmd->pipe_fd[1];
	}
	else if (cmd->prev && cmd->prev->is_piped && !cmd->is_piped)
	{
		cmd->pipe_in = cmd->prev->pipe_fd[0];
		cmd->pipe_out = 1;
	}
	return (EXIT_SUCCESS);
}

void	redirect_pipe_fds(t_cmd *cmd)
{
	if (cmd->pipe_in != 0)
	{
		dup2 (cmd->pipe_in, 0);
		close (cmd->pipe_in);
	}
	if (cmd->pipe_out != 1)
	{
		dup2 (cmd->pipe_out, 1);
		close (cmd->pipe_out);
	}
}

void	close_pipe_fds(t_cmd *cmd)
{
	if (cmd->is_piped && cmd->next != NULL)
		close (cmd->pipe_fd[1]);
	else if (cmd->is_piped && cmd->prev->is_piped)
	{
		close(cmd->prev->pipe_fd[0]);
		close(cmd->pipe_fd[1]);
	}
	else if (cmd->prev && cmd->prev->is_piped && !cmd->is_piped)
	{
		close(cmd->prev->pipe_fd[0]);
		close(cmd->prev->pipe_fd[1]);
	}
}
