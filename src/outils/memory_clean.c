/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_clean.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiacovel <tiacovel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 11:10:14 by tiacovel          #+#    #+#             */
/*   Updated: 2024/02/27 11:10:31 by tiacovel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/commands.h"

void	free_double_pointer(char **str)
{
	int	i;

	i = 0;
	while (!str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}
