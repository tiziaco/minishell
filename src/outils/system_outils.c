/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system_outils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiacovel <tiacovel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:07:28 by tiacovel          #+#    #+#             */
/*   Updated: 2024/03/11 17:27:45 by tiacovel         ###   ########.fr       */
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

bool	is_directory(char *cmd)
{
	struct stat	cmd_stat;

	ft_memset(&cmd_stat, 0, sizeof(cmd_stat));
	stat(cmd, &cmd_stat);
	return (S_ISDIR(cmd_stat.st_mode));
}
