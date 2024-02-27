/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiacovel <tiacovel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 15:03:26 by tiacovel          #+#    #+#             */
/*   Updated: 2024/02/27 11:35:41 by tiacovel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minish.h"

# define TMP_FILENAME "/home/tiacovel/core_curriculum/minishell/heredoc_tmp.tmp"
# define OP_SUCCESS	1
# define OP_FAIL	-1

void	execute_command(char *command, char **arguments, char **envp);

/* Built-in commnads */
void	ft_echo(char **str);
void	ft_cd(char *str);
void	ft_pwd(void);
int		ft_export(char ***envp, const char *name, const char *value);
int		ft_unset(char ***envp, const char *name);
int		ft_exit(char **str);
void	ft_env(char **envp);

/* Redirections */
void	heredoc(char *delimeter);

/* Outils */
char	*ft_strcat(char *dest, char *src);
char	*ft_strcpy(char *dest, char *src);
int		ft_strcmp(char *s1, char *s2);
void	free_double_pointer(char **str);