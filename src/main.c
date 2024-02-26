/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiacovel <tiacovel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 16:16:11 by tiacovel          #+#    #+#             */
/*   Updated: 2024/02/26 17:35:07 by tiacovel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/commands.h"

/* int	main(int argc, char **argv)
{
	// adfgdf
	return (0);
} */

int	main(int argc, char **argv, char **envp)
{
	char *command = "ls";
	char *args[] = {command, "-", NULL};
	/* ft_pwd();
	ft_cd("adsfsd");
	ft_pwd(); */
	//ft_env(envp);
	/* ft_export(&envp, "TEST_VAR", "xxxx");
	ft_env(envp);
	ft_unset(&envp, "TEST_VAR");
	ft_env(envp); */
	//heredoc("EOF");
	execute_command(command, args, envp);
	return (0);
}