/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minish.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiacovel <tiacovel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 16:12:13 by tiacovel          #+#    #+#             */
/*   Updated: 2024/03/04 14:48:27 by tiacovel         ###   ########.fr       */
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
# include <sys/stat.h>
# include <sys/wait.h>
# include <dirent.h>
# include <termios.h>

# include "libft.h"

/* Macros */
# define MSH_PROMPT "msh-> "
# define TMP_FILENAME "/home/tiacovel/core_curriculum/minishell/heredoc_tmp.tmp"

/* System error */
# define OP_SUCCESS		1
# define OP_FAIL		-1
# define MEM_ERROR  	2
# define ARG_ERROR  	3
# define CMD_ERROR		4
# define FORK_ERROR		5

/* Command errors */
# define INVALID_KEY	10
# define INVALID_PARM	11
# define CMD_NOT_FOUND	12
# define CMD_NOT_EXEC	13

/* Struct / typedef / enum */
typedef struct termios	t_term;

typedef struct s_cmd
{
	char	*command;
	char	**args;
	bool 	is_piped;
	bool 	redirect;
	t_cmd	*next;

}	t_cmd;

typedef struct s_data
{
	int		std_in;
	int		std_out;
	bool	background_mode;
	t_term	term;
	char	*line;
	char	**envp;
	char	*token; //To be modified accoring to our token struct
	t_cmd	*cmd;
	pid_t	pid;
}	t_data;

/* Initialization functions */
t_data	*init_data(char **envp);
void	exit_shell(t_data *data, int exit_code);

/* Environment functions */
int		search_key(char **envp, char *key);
int		get_env_size(char **envp);
char	*get_env_var(char *key, char *val);
char	**copy_environment(char **envp, int env_size);
int		set_var(t_data *data, char *key, char *val);
int		remove_var(t_data *data, int key_index);

/* Parsing */
int		parse_input(t_data *data);

/* Execution */
bool	is_builtin(char *arg);
bool	is_path(char *str);
int		exec_builtin(t_data *data);
int		exec_local_bin(t_data *data);
int		exec_bin(t_data *data);
int		execute_command(t_data *data);

/* Error handlers */
int		sys_error(int err_code);
int		cmd_error(int err_code);

/* Outils */
char	*ft_strcat(char *dest, char *src);
char	*ft_strcpy(char *dest, char *src);
int		ft_strcmp(char *s1, char *s2);
void	free_pointer(void *ptr);
void	free_double_pointer(char **str);
void	free_data(t_data *data, bool clear_all);

#endif
