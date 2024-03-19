/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 19:17:06 by jkaller           #+#    #+#             */
/*   Updated: 2024/03/19 21:04:18 by jkaller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minish.h"
#include "../../../include/parser.h"
#include "../../../include/libft.h"
#include "../../../include/commands.h"
#include <unistd.h>

char	*realloc_string(char *str, int str_len)
{
	char	*new_str;

	new_str = (char *)malloc(sizeof(char) * str_len);
	if (new_str == NULL) 
		return (NULL);
	if (str != NULL)
		strcpy(new_str, str);
	return (new_str);
}

void remove_quotes(t_token **token)
{
	char *value = (*token)->value;
	int i = 0;
	int j = 0;
	bool in_quotes = false;
	while (value[i] != '\0') {
		if (value[i] == '\\') {
			// Handle escaped characters
			if (value[i + 1] != '\0') {
				value[j++] = value[i + 1];
				i += 2;
			}
			else {
				// Backslash at the end of the string, treat it as a literal backslash
				value[j++] = value[i++];
			}
		}
		else if (value[i] == '\'' || value[i] == '\"') {
			// Skip quotes
			in_quotes = !in_quotes;
			i++;
		}
		else {
			// Copy characters excluding quotes
			value[j++] = value[i++];
		}
	}
	value[j] = '\0'; // Terminate the string
	(*token)->value = realloc((*token)->value, strlen(value) + 1); // Resize the token value
}

bool	quotes_in_string(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			return (true);
		i++;
	}
	return (false);
}

int	check_for_quotes(t_token *token_stack)
{
	t_token	*tmp;

	tmp = token_stack;
	while (tmp)
	{
		if (quotes_in_string(tmp->value) == true
			&& (!tmp->prev
				|| (tmp->prev && tmp->prev->type != HEREDOC_TOKEN)))
			remove_quotes(&tmp);
		tmp = tmp->next;
	}
	return (0);
}