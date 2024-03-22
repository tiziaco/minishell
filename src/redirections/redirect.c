/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiacovel <tiacovel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:26:50 by tiacovel          #+#    #+#             */
/*   Updated: 2024/03/22 12:41:38 by tiacovel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/commands.h"

/* int	restore_std_io(t_data *data, t_cmd *cmd)
{
	int	ret;

	ret = EXIT_SUCCESS;
	if (!cmd)
		return (ret);
	if (cmd->redirections->fd_in != data->std_in)
	{
		if (dup2(data->std_in, STDIN_FILENO) == -1)
			ret = EXIT_FAILURE;
		// close(io->stdin_backup);
	}
	if (cmd->redirections->fd_out != data->std_out)
	{
		if (dup2(data->std_out, STDOUT_FILENO) == -1)
			ret = EXIT_FAILURE;
		// close(io->stdout_backup);
	}
	return (ret);
} */

int	restore_std_io(t_data *data, t_cmd *cmd)
{
	if (!cmd)
		return (EXIT_SUCCESS);
	if (dup2(data->std_in, STDIN_FILENO) == -1)
		return (EXIT_FAILURE);
	if (dup2(data->std_out, STDOUT_FILENO) == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	set_redirection(t_data *data, t_cmd *cmd)
{
	t_redirect	*redirection;
	int			status;

	if (!cmd->redirections)
		return (EXIT_SUCCESS);
	redirection = cmd->redirections;
	while (redirection)
	{
		if (redirection->redirect == OUTPUT_TOKEN)
			status = output_truncate(redirection);
		else if (redirection->redirect == APPEND_TOKEN)
			status = output_append(redirection);
		else if (redirection->redirect == INPUT_TOKEN)
			status = input_redirection(redirection);
		else if (redirection->redirect == HEREDOC_TOKEN)
			status = input_heredoc(redirection);
		redirection = redirection->next;
	}
	
	return (EXIT_SUCCESS);
}
