/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiacovel <tiacovel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:26:50 by tiacovel          #+#    #+#             */
/*   Updated: 2024/03/06 17:03:10 by tiacovel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/commands.h"

int	restore_std_io(t_data *data, t_cmd *cmd)
{
	int	ret;

	ret = EXIT_SUCCESS;
	if (!cmd)
		return (ret);
	if (cmd->fd_in != data->std_in)
	{
		if (dup2(data->std_in, STDIN_FILENO) == -1)
			ret = EXIT_FAILURE;
		// close(io->stdin_backup);
	}
	if (cmd->fd_out != data->std_out)
	{
		if (dup2(data->std_out, STDOUT_FILENO) == -1)
			ret = EXIT_FAILURE;
		// close(io->stdout_backup);
	}
	return (ret);
}

/* redirect_io:
*	Duplicates the input and output fds to the standard input and output.
*	Backs up the standard input and output before replacing them in order
*	to restore them after execution.
*	Returns 1 for success, 0 in case of error.
*/
int	set_redirection(t_data *data, t_cmd *cmd)
{
	if (cmd->redirect == RED_OUT_TRUNC)
		return (output_truncate(cmd));
	else if (cmd->redirect == RED_OUT_APP)
		return (output_append(cmd));
	else if (cmd->redirect == RED_IN)
		return (input_redirection(cmd));
	else if (cmd->redirect == RED_IN_HERE)
		return (input_heredoc(cmd));
	return (EXIT_SUCCESS);
}
/* int	redirect_io(t_data *data, t_cmd *cmd)
{
	int	ret;

	ret = EXIT_SUCCESS;
	if (!cmd)
		return (ret);
	io->stdin_backup = dup(STDIN_FILENO);
	if (io->stdin_backup == -1)
		ret = errmsg_cmd("dup", "stdin backup", strerror(errno), false);
	io->stdout_backup = dup(STDOUT_FILENO);
	if (io->stdout_backup == -1)
		ret = errmsg_cmd("dup", "stdout backup", strerror(errno), false);
	if (io->fd_in != -1)
		if (dup2(io->fd_in, STDIN_FILENO) == -1)
			ret = errmsg_cmd("dup2", io->infile, strerror(errno), false);
	if (io->fd_out != -1)
		if (dup2(io->fd_out, STDOUT_FILENO) == -1)
			ret = errmsg_cmd("dup2", io->outfile, strerror(errno), false);
	return (ret);
} */
