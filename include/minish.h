/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minish.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 16:12:13 by tiacovel          #+#    #+#             */
/*   Updated: 2024/03/19 15:15:29 by jkaller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISH_H
# define MINISH_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <limits.h>
# include <signal.h>
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
# include "parser.h"

/* System vars */
# define MSH_PROMPT "msh-> "
# define TMP_FILENAME "/tmp/heredoc_tmp.tmp"
//# define TMP_FILENAME "/home/tiacovel/core_curriculum/minishell/heredoc_tmp.tmp"

/* Redirections */
# define RED_OUT_APP	1
# define RED_OUT_TRUNC	2
# define RED_IN			3
# define RED_IN_HERE	4

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

/* Redirection errors */
# define FILE_NF		20
# define RED_IN_ERR		21
# define RED_OUT_ERR	22
# define INVALID_FNAME	23

/* Tokenizer errors */
# define EOF_ERROR		24

/* Struct / typedef / enum */
typedef struct termios	t_term;

typedef struct s_cmd
{
	char			*command;
	char			**args;
	bool			is_piped;
	int				redirect;
	int				*pipe_fd;
	char			*file_name;
	char			*heredoc_delim;
	int				pipe_in;
	int				pipe_out;
	int				argc;
	int				fd_in;
	int				fd_out;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}	t_cmd;

typedef struct s_data
{
	int		std_in;
	int		std_out;
	bool	background_mode;
	t_term	term;
	char	*main_path;
	char	*line;
	char	**envp;
	t_table	*parsing_table;
	int		table_length;
	t_cmd	*cmd;
	pid_t	pid;
}	t_data;

/* Initialization functions */
t_data	*init_data(char **envp);
t_table	*init_parsing_table(t_data *data);
void	sigquit_handler(int num);
void	init_signals(t_data *data);
void	exit_shell(t_data *data, int exit_code);

/* Signals */
void	sigint_handler(int num);
void	sigquit_handler(int num);

/* Environment functions */
int		search_key(char **envp, char *key);
int		get_env_size(char **envp);
char	*get_env_var(char *key, char *val);
char	**copy_environment(char **envp, int env_size);
int		set_var(t_data *data, char *key, char *val);
int		remove_var(t_data *data, int key_index);

/* Redirections and pipes */
int		init_pipes(t_data *data);
int		set_pipe_fds(t_cmd *cmds, t_cmd *cmd);
void	close_pipe_fds(t_cmd *cmds, t_cmd *skip_cmd);

int		set_redirection(t_data *data, t_cmd *cmd);
int		restore_std_io(t_data *data, t_cmd *cmd);
int		output_truncate(t_cmd *cmd);
int		output_append(t_cmd *cmd);
int		input_redirection(t_cmd *cmd);
int		input_heredoc(t_cmd *cmd);

//parser
int		parse_input(t_data *data);
void	fill_command_struct(t_tree_node *tree, t_cmd *commands);
t_cmd	*add_to_command_struct(t_tree_node *tree);
void	ft_cmdadd_back(t_cmd **lst, t_cmd *new);
void	print_command_struct(t_cmd	*commands);
void    print_node(t_tree_node *tree);
void	print_command_args(char	**args);
void	print_entire_command_struct(t_cmd	*commands);
void	free_command_struct(t_cmd *command_stack);
void	free_all(t_token *token_stack, t_tree_node *abstract_syntax_tree);

/* Redirections and pipes */
int		init_pipes(t_data *data);
int		set_pipe_fds(t_cmd *cmds, t_cmd *cmd);
void	close_pipe_fds(t_cmd *cmds, t_cmd *skip_cmd);

int		set_redirection(t_data *data, t_cmd *cmd);
int		restore_std_io(t_data *data, t_cmd *cmd);
int		output_truncate(t_cmd *cmd);
int		output_append(t_cmd *cmd);
int		input_redirection(t_cmd *cmd);
int		input_heredoc(t_cmd *cmd);

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
int		red_error(int err_code);
int		tokenizer_error(int err_code);

/* Outils */
char	*get_cwd(void);
bool	is_directory(char *cmd);
char	*ft_strcat(char *dest, char *src);
char	*ft_strcpy(char *dest, char *src);
int		ft_strcmp(char *s1, char *s2);
void	free_pointer(void *ptr);
void	free_double_pointer(char **str);
void	free_data(t_data *data, bool clear_all);

#endif
