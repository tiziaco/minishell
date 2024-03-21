/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 19:17:06 by jkaller           #+#    #+#             */
/*   Updated: 2024/03/20 21:47:18 by jkaller          ###   ########.fr       */
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
	free(str);
	return (new_str);
}

void	remove_quotes(t_token **token_stack)
{
	char *value = (*token_stack)->value;
	int i = 0;
	int j = 0;
	char quote_type = value[0];
	bool inside_quote = false;

	while (value[i] != '\0')
	{
		if (value[i] == '\\')
		{
			if (value[i + 1] == '\"') {
				value[j++] = value[i + 1];
				i += 2;
			}
			else
				value[j++] = value[i++];
		}
		else if ((value[i] == '\'' || value[i] == '\"') && inside_quote == false)
		{
			quote_type = value[i];
			i++;
			inside_quote = true;
		}
		else if (value[i] == quote_type)
		{
			quote_type = value[0];
			i++;
			inside_quote = false;
		}
		else
			value[j++] = value[i++];
	}
	value[j] = '\0';
	(*token_stack)->value = realloc_string((*token_stack)->value, strlen(value) + 1);
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