/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 15:15:29 by jkaller           #+#    #+#             */
/*   Updated: 2024/03/21 18:00:03 by jkaller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minish.h"
#include "../../../include/parser.h"
#include "../../../include/libft.h"
#include "../../../include/commands.h"
#include <unistd.h>

int	tokenize_input(t_data *data, t_token **token_stack)
{
	int	i;
	int	token_status;
	int	start;

	*token_stack = NULL;
	i = -1;
	start = 0;
	token_status = 0;
	while (++i <= ft_strlen(data->line))
	{
		token_status = set_token_status(token_status, data->line, i);
		if (token_status == 0)
			start = tokenize_input_string(data->line, token_stack, &i, start);
	}
	if (token_status != 0)
	{
		tokenizer_error(EOF_ERROR);
		return (EXIT_FAILURE);
	}
	if (*token_stack == NULL || (*token_stack)->value == NULL)
		return (EXIT_FAILURE);
	check_for_quotes(*token_stack);
	check_for_expansions(*token_stack, data);
	return (EXIT_SUCCESS);
}
