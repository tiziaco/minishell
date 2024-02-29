/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_clean.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiacovel <tiacovel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 11:10:14 by tiacovel          #+#    #+#             */
/*   Updated: 2024/02/29 18:24:02 by tiacovel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/commands.h"

void	free_pointer(void *ptr)
{
	if (ptr != NULL)
	{
		free(ptr);
		ptr = NULL;
	}
}

void	free_double_pointer(char **str)
{
	int	i;

	i = 0;
	while (!str[i])
	{
		if (str[i] != NULL)
			free(str[i]);
		i++;
	}
	free(str);
}

void	free_data(t_data *data)
{
	if (data->envp != NULL)
		free_double_pointer(data->envp);
	if (data->cmd != NULL)
	{
		free_pointer(data->cmd->command);
		free_double_pointer(data->cmd->args);
	}
	if (data->line != NULL)
		free_pointer(data->line);
	if (data->token != NULL)
		free_pointer(data->line);
}
