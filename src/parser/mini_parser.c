/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiacovel <tiacovel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 12:00:50 by tiacovel          #+#    #+#             */
/*   Updated: 2024/03/04 15:43:41 by tiacovel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minish.h"

int	mini_parse_input(t_data *data)
{
	char **buffer;

	buffer = ft_split(data->line, ' ');
	if (!buffer)
		return (OP_FAIL);
	data->cmd->command = buffer[0];
	data->cmd->args = buffer;
	return (OP_SUCCESS);
}
