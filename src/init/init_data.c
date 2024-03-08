/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiacovel <tiacovel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 17:15:37 by tiacovel          #+#    #+#             */
/*   Updated: 2024/03/08 16:30:42 by tiacovel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/commands.h"
#include "../../include/parser.h"
// void	init_cmd(t_cmd *cmd)
// {
// 	cmd->command = NULL;
// 	cmd->args = NULL;
// 	cmd->file_name = NULL;
// 	cmd->heredoc_delim = NULL;
// 	cmd->pipe_fd = NULL;
// 	cmd->fd_in = -1;
// 	cmd->fd_out = -1;
// 	cmd->pipe_in = -1;
// 	cmd->pipe_out = -1;
// 	cmd->next = NULL;
// 	cmd->prev = NULL;
// }

t_data	*init_data(char **envp)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!data->cmd)
		return (NULL);
	data->envp = copy_environment(envp, get_env_size(envp));
	if (!data->envp)
		exit_shell(data, EXIT_FAILURE);
	data->std_in = dup(STDIN_FILENO);
	data->std_out = dup(STDOUT_FILENO);
	data->line = NULL;
	data->main_path = get_cwd();
	tcgetattr(STDIN_FILENO, &data->term);
	//init_cmd(data->cmd);
	data->parsing_table = init_parsing_table(data->main_path);
	return (data);
}

void	exit_shell(t_data *data, int exit_code)
{
	if (data)
	{
		/* if (data->cmd && data->cmd->io_fds)
			close_fds(data->cmd, true); */
		free_data(data, true);
	}
	exit(exit_code);
}
