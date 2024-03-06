/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiacovel <tiacovel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 17:15:37 by tiacovel          #+#    #+#             */
/*   Updated: 2024/03/05 12:42:57 by tiacovel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/commands.h"

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
	tcgetattr(STDIN_FILENO, &data->term);
	data->cmd->command = NULL;
	data->cmd->args = NULL;
	data->line = NULL;
	data->token = NULL;
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
