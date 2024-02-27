/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sys_errors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiacovel <tiacovel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 16:48:07 by tiacovel          #+#    #+#             */
/*   Updated: 2024/02/27 18:41:32 by tiacovel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/commands.h"

int	sys_error(int err_code)
{
	if (err_code == MEM_ERROR)
		printf("Memorey allocation failed");
	else if (err_code == ARG_ERROR)
		printf("The arguments are invalid.");
	return (err_code);
}
