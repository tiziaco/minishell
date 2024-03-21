/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 14:34:51 by jkaller           #+#    #+#             */
/*   Updated: 2024/03/21 18:04:02 by jkaller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minish.h"
#include "../../../include/parser.h"
#include "../../../include/libft.h"
#include "../../../include/commands.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void    delete_node(t_token **token_stack, t_token *node_to_delete)
{
    if (*token_stack == NULL || node_to_delete == NULL)
        return ;
    if (*token_stack == node_to_delete)
        *token_stack = node_to_delete->next;
    if (node_to_delete->next != NULL)
        node_to_delete->next->prev = node_to_delete->prev;
    if (node_to_delete->prev != NULL)
        node_to_delete->prev->next = node_to_delete->next;
    free(node_to_delete);
}

char*   expand_env(char *token_value, int *index)
{
	char    *env_value;
	char    *env_key;
	int     j;

	j = 0;
	(*index)++;
	env_key = ft_calloc(sizeof(char), ft_strlen(token_value));
	while (token_value[*index] != '$' && token_value[*index] != '\0'
		&& ft_isalpha(token_value[*index]) > 0)
	{
		env_key[j] = token_value[*index];
		(*index)++;
		j++;
	}
	env_key[j] = '\0';
	env_value = getenv(env_key);
	free(env_key);
	if (env_value == NULL)
	{
		return (NULL);
	}
	return (env_value);
}

char*   handle_expansion(char *token_value)
{
	char    *return_string;
	int		*index;

	*index = 0;
	return_string = ft_calloc(sizeof(char), ft_strlen(token_value));
	while (token_value[*index] != '\0')
	{
		ft_printf("index: %d\n", *index);
		if (token_value[*index] == '$')
		{
			return_string = ft_strjoin(return_string, expand_env(token_value, index));
		}
		else
		{
			return_string[*index] = token_value[*index];
			(*index)++;
		}
	}
	return (return_string);
}

void    check_for_expansions(t_token *token_stack)
{
    t_token *current;
    int     index;

    while (token_stack)
    {
        index = 0;
        current = token_stack;
        token_stack = token_stack->next;
        while (current->value[index] != '\0')
        {
            if (ft_strrchr(current->value, '$') != 0)
            {
                current->value = handle_expansion(current->value);
                if (current->value[0] == '\0')
                    delete_node(&token_stack, current);
            }
            index++;
        }
    }
}
