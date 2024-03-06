/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiacovel <tiacovel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:27:23 by tiacovel          #+#    #+#             */
/*   Updated: 2024/03/05 15:53:32 by tiacovel         ###   ########.fr       */
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
		if (tmp->is_piped || (tmp->prev && tmp->prev->is_piped))
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
int	set_pipe_fds(t_cmd *cmds, t_cmd *cmd)
{
	if (!cmd)
		return (EXIT_FAILURE);
	if (cmd->prev && cmd->prev->is_piped)
		dup2(cmd->prev->pipe_fd[0], STDIN_FILENO);
	if (cmd->is_piped)
		dup2(cmd->pipe_fd[1], STDOUT_FILENO);
	close_pipe_fds(cmds, cmd);
	return (EXIT_SUCCESS);
}

void	close_pipe_fds(t_cmd *cmds, t_cmd *skip_cmd)
{
	while (cmds)
	{
		if (cmds != skip_cmd && cmds->pipe_fd)
		{
			close(cmds->pipe_fd[0]);
			close(cmds->pipe_fd[1]);
		}
		cmds = cmds->next;
	}
}
