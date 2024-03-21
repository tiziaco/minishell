/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 14:43:49 by jkaller           #+#    #+#             */
/*   Updated: 2024/03/21 13:11:15 by jkaller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minish.h"
#include "../../../include/parser.h"
#include "../../../include/libft.h"
#include "../../../include/commands.h"
#include <unistd.h>

int	define_seperator(char *input, int index)
{
	if (((input[index] > 8 && input[index] < 14) || input[index] == 32))
		return (1);
	else if (input[index] == '|')
		return (PIPE_TOKEN);
	else if (input[index] == '<' && input[index + 1] == '<')
		return (HEREDOC_TOKEN);
	else if (input[index] == '>' && input[index + 1] == '>')
		return (APPEND_TOKEN);
	else if (input[index] == '<')
		return (INPUT_TOKEN);
	else if (input[index] == '>')
		return (OUTPUT_TOKEN);
	else if (input[index] == '\0')
		return (END_TOKEN);
	else
		return (0);
}

int	create_linked_redirection(char *input, t_token **token_stack,
	int index, int token_type)
{
	int		i;
	char	*sep;

	i = 0;
	if (token_type == APPEND_TOKEN || token_type == HEREDOC_TOKEN)
	{
		sep = malloc(sizeof(char) * 3);
		if (!sep)
			return (1);
		while (i < 2)
			sep[i++] = input[index++];
		sep[i] = '\0';
		ft_lstadd_back_token(token_stack, ft_lstnew_token(sep, token_type));
	}
	else
	{
		sep = malloc(sizeof(char) * 2);
		if (!sep)
			return (1);
		while (i < 1)
			sep[i++] = input[index++];
		sep[i] = '\0';
		ft_lstadd_back_token(token_stack, ft_lstnew_token(sep, token_type));
	}
	free(sep);
	return (0);
}

int	create_linked_word(char *input, t_token **token_stack, int index, int start)
{
	int		i;
	char	*word;

	i = 0;
	word = malloc(sizeof(char) * (index - start + 1));
	if (!word)
		return (1);
	while (start < index)
	{
		word[i] = input[start];
		start++;
		i++;
	}
	word[i] = '\0';
	ft_lstadd_back_token(token_stack, ft_lstnew_token(word, WORD_TOKEN));
	free(word);
	return (0);
}

int	tokenize_input_string(char *input_str,
	t_token **token_stack, int *index, int start)
{
	int		token_type;

	token_type = define_seperator(input_str, (*index));
	if (token_type)
	{
		if ((*index) != 0 && define_seperator(input_str, (*index) - 1) == 0)
			create_linked_word(input_str, token_stack, (*index), start);
		if (token_type == APPEND_TOKEN || token_type == HEREDOC_TOKEN
			|| token_type == PIPE_TOKEN || token_type == INPUT_TOKEN
			|| token_type == OUTPUT_TOKEN || token_type == END_TOKEN)
		{
			create_linked_redirection(input_str,
				token_stack, (*index), token_type);
			if (token_type == APPEND_TOKEN || token_type == HEREDOC_TOKEN)
				(*index)++;
		}
		start = (*index) + 1;
	}
	return (start);
}


int	set_token_status(int token_status, char *line, int index)
{
	if (index > 0 && line[index - 1] == '\\')
		return (token_status);
	else if (line[index] == '\'' && token_status == 0)
		token_status = 1;
	else if (line[index] == '\"' && token_status == 0)
		token_status = 2;
	else if (line[index] == '\'' && token_status == 1)
		token_status = 0;
	else if (line[index] == '\"' && token_status == 2)
		token_status = 0;
	return (token_status);
}