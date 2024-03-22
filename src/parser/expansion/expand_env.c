/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 14:34:51 by jkaller           #+#    #+#             */
/*   Updated: 2024/03/22 17:23:49 by jkaller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minish.h"
#include "../../../include/parser.h"
#include "../../../include/libft.h"
#include "../../../include/commands.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

char	*ft_strjoin_free(char const *s1, char const *s2)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	new = (char *)malloc(sizeof(char) * ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!new)
		return (NULL);
	while (s1[i])
	{
		new[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		new[i] = s2[j];
		i++;
		j++;
	}
	new[i] = '\0';
	free((char *)s1);
	return (new);
}

void	delete_node(t_token **token_stack, t_token *node_to_delete)
{
	if (*token_stack == NULL || node_to_delete == NULL)
		return ;
	if (*token_stack == node_to_delete)
		*token_stack = node_to_delete->next;
	if (node_to_delete->next != NULL)
		node_to_delete->next->prev = node_to_delete->prev;
	if (node_to_delete->prev != NULL)
		node_to_delete->prev->next = node_to_delete->next;
	free(node_to_delete->value);
	free(node_to_delete);
}

char	*expand_env(char *token_value, int *index)
{
	char	*env_value;
	char	*env_key;
	int		j;

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
		return ("\0");
	}
	return (env_value);
}

char	*handle_expansion(char *token_value)
{
	char	*return_string;
	int		index;

	index = 0;
	return_string = ft_calloc(sizeof(char), ft_strlen(token_value));
	while (token_value[index] != '\0')
	{
		if (token_value[index] == '$' && (token_value[index + 1] != ' ' && token_value[index + 1] != '\0'))
			return_string = ft_strjoin_free(return_string,
					expand_env(token_value, &index));
		else
		{
			return_string[index] = token_value[index];
			index++;
		}
	}
	free(token_value);
	return (return_string);
}

void	check_for_expansions(t_token *token_stack)
{
	t_token	*current;
	int		index;

	while (token_stack)
	{
		index = 0;
		current = token_stack;
		token_stack = token_stack->next;
		if (ft_strrchr(current->value, '$') != 0)
		{
			current->value = handle_expansion(current->value);
			if (current->value[0] == '\0')
				delete_node(&token_stack, current);
		}
	}
}
