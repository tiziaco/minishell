/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiacovel <tiacovel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 14:33:50 by tiacovel          #+#    #+#             */
/*   Updated: 2024/03/26 16:25:33 by tiacovel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/commands.h"
// #include <linux/limits.h>

int	ft_echo(char **str)
{
	int		i;
	bool	n_flag;

	i = 1;
	n_flag = false;
	while (str[i] && is_n_flag(str[i]))
	{
		n_flag = true;
		i++;
	}
	while (str[i] != NULL)
	{
		printf("%s", str[i]);
		if (str[i + 1] != NULL)
			printf("%c", ' ');
		i++;
	}
	if (!n_flag)
		printf("\n");
	return (EXIT_SUCCESS);
}

int	ft_cd(char *str)
{
	if (chdir(str) == -1)
	{
		printf("ft_cd: no such file or directory: %s\n", str);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	ft_pwd(void)
{
	char	*cwd;

	cwd = (char *)malloc(PATH_MAX);
	if (!cwd)
		return (sys_error(MEM_ERROR));
	if (getcwd(cwd, PATH_MAX) != NULL)
		printf("%s\n", cwd);
	else
	{
		free(cwd);
		return (sys_error(CMD_ERROR));
	}
	free(cwd);
	return (EXIT_SUCCESS);
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
	return (EXIT_SUCCESS);
}
