/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiacovel <tiacovel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 14:33:50 by tiacovel          #+#    #+#             */
/*   Updated: 2024/03/25 12:02:39 by tiacovel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/commands.h"
// #include <linux/limits.h>

int	ft_echo(char **str)
{
	int	i;
	char *test;

	i = 1;
	while (str[i] != NULL)
	{
		test = str[i];
		ft_printf("%s", str[i]);
		if (str[i + 1] != NULL)
			ft_printf("%c", ' ');
		i++;
	}
	printf("\n");
	return (OP_SUCCESS);
}

int	ft_cd(char *str)
{
	if (chdir(str) == -1)
	{
		ft_printf("ft_cd: no such file or directory: %s\n", str);
		return (OP_FAIL);
	}
	return (OP_SUCCESS);
}

int	ft_pwd(void)
{
	char	*cwd;

	cwd = (char *)malloc(PATH_MAX);
	if (!cwd)
		return (sys_error(MEM_ERROR));
	if (getcwd(cwd, PATH_MAX) != NULL)
		ft_printf("%s\n", cwd);
	else
	{
		free(cwd);
		return (sys_error(CMD_ERROR));
	}
	free(cwd);
	return (OP_SUCCESS);
}

void	ft_exit(t_data *data)
{
	exit_shell(data, EXIT_SUCCESS);
}

int	ft_env(char **envp)
{
	char	**curr_env;

	curr_env = envp;
	while (*curr_env != NULL)
	{
		printf("%s\n", *curr_env);
		curr_env++;
	}
	return (OP_SUCCESS);
}
