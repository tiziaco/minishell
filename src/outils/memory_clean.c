/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_clean.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiacovel <tiacovel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 11:10:14 by tiacovel          #+#    #+#             */
/*   Updated: 2024/03/26 17:23:58 by tiacovel         ###   ########.fr       */
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
/* 	if (data->cmd)
		free_cmd(data->cmd);
	if (data->line)
		free_pointer(data->line); */
	if (clear_all)
	{
		if (data && data->envp)
			free_double_pointer(data->envp);
		if (data && data->main_path)
			free(data->main_path);
		if (data && data->parsing_table)
			free(data->parsing_table);
		rl_clear_history();
		free(data);
	}
}
