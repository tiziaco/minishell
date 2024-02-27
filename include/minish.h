/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minish.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiacovel <tiacovel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 16:12:13 by tiacovel          #+#    #+#             */
/*   Updated: 2024/02/27 18:38:59 by tiacovel         ###   ########.fr       */
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
# define OP_SUCCESS	1
# define OP_FAIL	-1
# define MEM_ERROR  2
# define ARG_ERROR  3

/* Struct / typedef / enum */
typedef struct termios	t_term;

typedef struct s_data
{
	int		std_in;
	int		std_out;
	bool	background_mode;
	t_term	term;
	char	*line;
	char	***envp;
	char	*token;
}	t_data;

/* Initialization functions */
t_data	*init_data(char **envp);

/* Utility functions */

/* Error handlers */
int		sys_error(int err_code);

#endif
