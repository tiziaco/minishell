/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 15:15:29 by jkaller           #+#    #+#             */
/*   Updated: 2024/03/18 20:34:14 by jkaller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minish.h"
#include "../../../include/parser.h"
#include "../../../include/libft.h"
#include <unistd.h>

void	create_linked_token(char *input, t_token **token_stack)
{
	t_token		*new_token;

	new_token = NULL;
	if (!input)
		new_token = ft_lstnew_token(NULL, (int)END_TOKEN);
	else if (ft_strncmp("|", input, ft_strlen(input)) == 0)
		new_token = ft_lstnew_token(input, (int)PIPE_TOKEN);
	else if (ft_strncmp("<", input, ft_strlen(input)) == 0)
		new_token = ft_lstnew_token(input, (int)REDIRECTION_INPUT_TOKEN);
	else if (ft_strncmp(">", input, ft_strlen(input)) == 0)
		new_token = ft_lstnew_token(input, (int)REDIRECTION_OUTPUT_TOKEN);
	else if (ft_strncmp("<<", input, ft_strlen(input)) == 0)
		new_token = ft_lstnew_token(input, (int)REDIRECTION_HEREDOC_TOKEN);
	else if (ft_strncmp(">>", input, ft_strlen(input)) == 0)
		new_token = ft_lstnew_token(input, (int)REDIRECTION_APPEND_TOKEN);
	else
		new_token = ft_lstnew_token(input, WORD_TOKEN);
	ft_lstadd_back_token(token_stack, new_token);
}

void	create_linked_list(char *input, t_token **token_stack,
	int len, int quotes)
{
	char	*token;

	token = (char *)malloc((len - quotes * 2 + 1) * sizeof(char));
	if (!token)
		exit(EXIT_FAILURE);
	strncpy(token, input + quotes, len - quotes * 2);
	token[len - quotes * 2] = '\0';
	create_linked_token(token, token_stack);
	free(token);
}

int	handle_quotes(char *quote, int len)
{
	char	quote_type;

	quote_type = quote[len];
	len++;
	while (quote[len] != quote_type && quote[len] != '\0')
	{
		if (quote[len] == '\\' && quote[len + 1] == quote_type)
			len += 2;
		else
			len++;
	}
	if (quote[len] == quote_type)
		len++;
	else if (quote[len] == '\0')
		return (EXIT_FAILURE);
	return (len);
}

int	tokenize_input_string(char *input_str, t_token **token_stack)
{
	int		len;

	while (*input_str)
	{
		while (*input_str == ' ' || *input_str == '\t')
			input_str++;
		if (*input_str != '\0' && *input_str != ' ' && *input_str != '\t')
		{
			len = 0;
			if (*input_str == '"' || *input_str == '\'')
			{
				len = handle_quotes(input_str, len);
				if (len == EXIT_FAILURE)
					return (EXIT_FAILURE);
				create_linked_list(input_str, token_stack, len, 1);
			}
			else
			{
				while (input_str[len] != '\0' && input_str[len] != ' ' && input_str[len] != '\t')
					len++;
				create_linked_list(input_str, token_stack, len, 0);
			}
			input_str += len;
		}
		if (*input_str == '\0')
			create_linked_token(NULL, token_stack);
	}
	return (EXIT_SUCCESS);
}

int	tokenize_input(char *input_line, t_token **token_stack)
{
	int		i;

	*token_stack = NULL;
	tokenize_input_string(input_line, token_stack);
	if (*token_stack == NULL || (*token_stack)->value == NULL)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
