/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiacovel <tiacovel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 15:03:26 by tiacovel          #+#    #+#             */
/*   Updated: 2024/02/19 15:10:33 by tiacovel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minish.h"
# include <stdio.h>

void	ft_echo(char **str);
void	ft_cd(char *str);
void	ft_pwd(void);
int		ft_export(char ***envp, const char *name, const char *value);
int		ft_unset(char ***envp, const char *name);
int		ft_exit(char **str);
void	ft_env(char **envp);