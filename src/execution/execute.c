/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiacovel <tiacovel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 10:28:34 by tiacovel          #+#    #+#             */
/*   Updated: 2024/03/01 12:38:53 by tiacovel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/commands.h"

int	execute_command(t_data *data)
{
	char	*command_path;

	if (is_builtin(data->cmd->command))
		exec_builtin(data);
	/* else if (is_path()) */
	return (OP_SUCCESS);
}
