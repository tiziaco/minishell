/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minish.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiacovel <tiacovel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 16:12:13 by tiacovel          #+#    #+#             */
/*   Updated: 2024/02/29 18:24:17 by tiacovel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISH_H
# define MINISH_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <limits.h>
# include <stdbool.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <dirent.h>
# include <termios.h>

# include "libft.h"

/* Macros */
# define MSH_PROMPT "msh-> "
# define TMP_FILENAME "/home/tiacovel/core_curriculum/minishell/heredoc_tmp.tmp"

/* Error codes */
# define OP_SUCCESS		1
# define OP_FAIL		-1
# define MEM_ERROR  	2
# define ARG_ERROR  	3
# define CMD_ERROR		4
# define INVALID_KEY	10
# define INVALID_PARM	11

/* Struct / typedef / enum */
typedef struct termios	t_term;

typedef struct s_cmd
{
	char	*command;
	char	**args;
}	t_cmd;

typedef struct s_data
{
	int		std_in;
	int		std_out;
	bool	background_mode;
	t_term	term;
	char	*line;
	char	***envp;
	char	*token;
	t_cmd	*cmd;
}	t_data;

/* Initialization functions */
t_data	*init_data(char **envp);

/* Environment functions */
int		search_key(char ***envp, char *key);
int		get_env_size(char **envp);
char	*get_env_var(char *key, char *val);
char	**copy_environment(char **envp, int env_size);
int		set_var(t_data *data, char *key, char *val);
int		remove_var(t_data *data, int key_index);

/* Error handlers */
int		sys_error(int err_code);
int		cmd_error(int err_code);

/* Outils */
char	*ft_strcat(char *dest, char *src);
char	*ft_strcpy(char *dest, char *src);
int		ft_strcmp(char *s1, char *s2);
void	free_pointer(void *ptr);
void	free_double_pointer(char **str);
void	free_data(t_data *data);

#endif
