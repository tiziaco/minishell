/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 17:41:25 by jkaller           #+#    #+#             */
/*   Updated: 2024/02/15 17:41:55 by jkaller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <limits.h>
# include <stdbool.h>

# include "libft.h"

/* Struct / typedef / enum */
//no dollar sign here because it should be part of a word and is never seperate, there is either $word or $? (which is also a word)
typedef enum
{
	WORD_TOKEN,
	PIPE_TOKEN,
	REDIRECTION_INPUT_TOKEN,
	REDIRECTION_OUTPUT_TOKEN,
	REDIRECTION_HEREDOC_TOKEN,
	REDIRECTION_APPEND_TOKEN,
	END_TOKEN,
} TokenTypes;

typedef struct s_token
{
	char			*value;
	TokenTypes		type;
	struct s_token	*next;
}	t_token;

/* Initialization functions */
int parse_input(int argc, char *argv[]);
int	tokenize_input(int argc, char *argv[], t_token **token_stack);

/* Utility functions */
void	ft_lstadd_back_token(t_token **lst, t_token *new);
t_token	*ft_lstnew_token(char *value, TokenTypes token_type);
void	free_token_stack(t_token *token_stack);
void	print_token_stack(t_token *token_stack);

#endif