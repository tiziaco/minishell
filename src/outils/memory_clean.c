/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_clean.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 11:10:14 by tiacovel          #+#    #+#             */
/*   Updated: 2024/03/22 17:25:57 by jkaller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/commands.h"

void	free_pointer(void *ptr)
{
	if (ptr)
	{
		free(ptr);
		ptr = "\0";
	}
}

void	free_double_pointer(char **str)
{
	int	i;

	if (str == NULL)
		return ;
	i = 0;
	while (str[i])
	{
		free(str[i]);
		str[i] = NULL;
		i++;
	}
	free(str);
}

void	free_cmd(t_cmd *cmd)
{
	if (cmd == NULL)
		return ;
	free_pointer(cmd->command);
	free_double_pointer(cmd->args);
	free(cmd);
	cmd = NULL;
}

void	free_data(t_data *data, bool clear_all)
{
	if (data == NULL)
		return ;
	if (clear_all && data)
	{
		if (data->envp)
			free_double_pointer(data->envp);
		if (data->line)
			free_pointer(data->line);
		if (data->main_path)
			free_pointer(data->main_path);
		if (data->line)
			free_pointer(data->line);
		rl_clear_history();
		free(data);
	}
}
