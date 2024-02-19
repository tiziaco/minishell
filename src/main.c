/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiacovel <tiacovel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 16:16:11 by tiacovel          #+#    #+#             */
/*   Updated: 2024/02/19 15:23:57 by tiacovel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/commands.h"

/* int	main(int argc, char **argv)
{
	// adfgdf
	return (0);
} */

extern char **environ;

int	main(int argc, char **argv, char **envp)
{
	/* ft_pwd();
	ft_cd("adsfsd");
	ft_pwd(); */
	//ft_env(envp);
	ft_export(&envp, "TEST_VAR", "xxxx");
	ft_env(envp);
	return (0);
}