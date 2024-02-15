/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 17:48:07 by jkaller           #+#    #+#             */
/*   Updated: 2024/02/15 15:28:19 by jkaller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//echo "Hello World" | cat -e my_file
#include "../../include/minish.h"
#include "../../include/parsing.h"
#include "../../include/libft.h"
#include <unistd.h>

int	parse_input(int argc, char *argv[])
{
	t_token	*token_stack;

	tokenize_input(argc, argv, &token_stack);
	return (0);
}
