/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiacovel <tiacovel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 15:03:26 by tiacovel          #+#    #+#             */
/*   Updated: 2024/03/11 17:20:09 by tiacovel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minish.h"

/* Built-in commnads */
int		ft_echo(char **str);
int		ft_cd(char *str);
int		ft_pwd(void);
int		ft_export(t_data *data, char **args);
int		ft_unset(t_data *data, char **args);
int		ft_exit(void);
int		ft_env(char **envp);
