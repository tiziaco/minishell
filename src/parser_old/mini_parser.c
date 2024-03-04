/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 12:00:50 by tiacovel          #+#    #+#             */
/*   Updated: 2024/03/04 18:28:45 by jkaller          ###   ########.fr       */
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
