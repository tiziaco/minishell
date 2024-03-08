/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 15:15:29 by jkaller           #+#    #+#             */
/*   Updated: 2024/03/08 14:33:45 by jkaller          ###   ########.fr       */
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

void	create_linked_list(char *input, t_token **token_stack, int len)
{
	char	*token;

	token = (char *)malloc((len + 1) * sizeof(char));
	ft_strlcpy(token, input, len + 1);
	create_linked_token(token, token_stack);
	free(token);
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
			if (input_str[len] == '"')
			{
				len++;
				while (input_str[len] != '"' && input_str[len] != '\0')
				{
					len++;
				}
				if (input_str[len] == '"')
					len++; //COMMENT: what if the string ends without a closing double.
			}
			else
			{
				while (input_str[len] != '\0' && input_str[len] != ' ' && input_str[len] != '\t')
					len++;
			}
			create_linked_list(input_str, token_stack, len);
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
	if (tokenize_input_string(input_line, token_stack) == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	else
		return (EXIT_FAILURE);
	//print_token_stack(*token_stack);
}