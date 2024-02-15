/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 15:15:29 by jkaller           #+#    #+#             */
/*   Updated: 2024/02/15 19:20:06 by jkaller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minish.h"
#include "../../include/parsing.h"
#include "../../include/libft.h"
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

void	tokenize_input_string(char *input_str, t_token **token_stack)
{
	int		len;
	char	*token;

	while (*input_str)
	{
		while (*input_str == ' ' || *input_str == '\t')
			input_str++;
		if (*input_str != '\0' && *input_str != ' ' && *input_str != '\t')
		{
			len = 0;
			while (input_str[len] != '\0' && input_str[len] != ' '
				&& input_str[len] != '\t')
				len++;
			token = (char *)malloc((len + 1) * sizeof(char));
			ft_strlcpy(token, input_str, len + 1);
			create_linked_token(token, token_stack);
			free(token);
			input_str += len;
		}
		if (*input_str == '\0')
			create_linked_token(NULL, token_stack);
	}
}

int	tokenize_input(int argc, char *argv[], t_token **token_stack)
{
	int		i;

	*token_stack = NULL;
	if (argc == 2)
	{
		tokenize_input_string(argv[1], token_stack);
	}
	else if (argc > 2)
	{
		i = 1;
		while (i < argc)
		{
			create_linked_token(argv[i], token_stack);
			i++;
		}
	}
	print_token_stack(*token_stack);
	free_token_stack(*token_stack);
	return (0);
}
