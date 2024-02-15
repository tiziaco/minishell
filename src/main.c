/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 16:16:11 by tiacovel          #+#    #+#             */
/*   Updated: 2024/02/15 17:41:15 by jkaller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minish.h"
#include "../include/parsing.h"
#include "../include/libft.h"

int	main(int argc, char **argv)
{
	if (argc >= 2)
	{
		parse_input(argc, argv);
	}
	return (0);
}