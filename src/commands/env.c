/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiacovel <tiacovel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 14:40:09 by tiacovel          #+#    #+#             */
/*   Updated: 2024/02/19 15:04:45 by tiacovel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/commands.h"

void	ft_env(char **envp)
{
	char	**curr_env;
	
	curr_env = envp;
	while (*curr_env != NULL)
	{
		printf("%s\n", *curr_env);
		curr_env++;
	}
	return ;
}