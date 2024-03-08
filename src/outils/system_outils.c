/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system_outils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiacovel <tiacovel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:07:28 by tiacovel          #+#    #+#             */
/*   Updated: 2024/03/08 15:12:18 by tiacovel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/commands.h"

char	*get_cwd(void)
{
	char	*cwd;

	cwd = (char *)malloc(PATH_MAX);
	if (!cwd)
		return (NULL);
	if (getcwd(cwd, PATH_MAX) == NULL)
		return(NULL);
    return(cwd);
}
