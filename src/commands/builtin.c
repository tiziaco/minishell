/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiacovel <tiacovel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 14:33:50 by tiacovel          #+#    #+#             */
/*   Updated: 2024/02/15 16:03:09 by tiacovel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/commands.h"

void	ft_echo(char **str)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
	{
		ft_printf("%s", str[i]);
		if (str[i + 1] != NULL)
			ft_printf("%c", ' ');
		i++;
	}
}

void	ft_cd(char *str)
{
	if (chdir(str) == -1)
		ft_printf("ft_cd: no such file or directory: %s\n", str);
	return ;
}

void	ft_pwd(void)
{
	char	*cwd;

	cwd = (char *)malloc(PATH_MAX);
	if (!cwd)
	{
		perror("malloc() failed");
		return ;
	}
	if (getcwd(cwd, PATH_MAX) != NULL)
		ft_printf("%s\n", cwd);
	else
	{
		perror("getcwd() error");
		free(cwd);
	}
	free(cwd);
	return ;
}

void	ft_export(char *str)
{
	return ;
}

void	ft_unset(char *str)
{
	return ;
}
