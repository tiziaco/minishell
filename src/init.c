/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiacovel <tiacovel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 17:15:37 by tiacovel          #+#    #+#             */
/*   Updated: 2024/02/29 18:07:23 by tiacovel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/commands.h"

t_data	*init_data(char **envp)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->envp = copy_environment(envp, get_env_size(envp));
	// Call exit_shell() if data->envp is NULL
	// Save also the default STDIN and STDOUT
	data->line = NULL;
	data->token = NULL;
	return (data);
}
