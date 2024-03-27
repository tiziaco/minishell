/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiacovel <tiacovel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 17:15:37 by tiacovel          #+#    #+#             */
/*   Updated: 2024/03/27 16:00:55 by tiacovel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/commands.h"
#include "../../include/parser.h"

t_data	*init_data(char **envp)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->envp = copy_environment(envp, get_env_size(envp));
	if (!data->envp)
		exit_shell(data, EXIT_FAILURE);
	data->std_in = dup(STDIN_FILENO);
	data->std_out = dup(STDOUT_FILENO);
	data->line = NULL;
	data->pid = 0;
	data->table_length = 0;
	data->main_path = get_cwd();
	tcgetattr(STDIN_FILENO, &data->term);
	data->parsing_table = init_parsing_table(data);
	return (data);
}

void	exit_shell(t_data *data, int exit_code)
{
	if (data)
		free_data(data, true);
	exit(exit_code);
}
