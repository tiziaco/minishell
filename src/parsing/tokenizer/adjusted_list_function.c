/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adjusted_list_function.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 12:18:06 by jkaller           #+#    #+#             */
/*   Updated: 2024/03/02 17:59:49 by jkaller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minish.h"
#include "../../../include/parsing.h"
#include "../../../include/libft.h"
#include <unistd.h>

void	ft_lstadd_back_token(t_token **lst, t_token *new)
{
	t_token	*last;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = *lst;
	while (last && last->next)
		last = last->next;
	last->next = new;
}

t_token	*ft_lstnew_token(char *value, TokenTypes token_type)
{
	t_token	*node;

	node = (t_token *)malloc(sizeof(t_token));
	node->value = 0;
	node->type = 0;
	if (!node)
		return (NULL);
	if (value == NULL)
		node->value = NULL;
	else
		node->value = ft_strdup(value);
	node->type = token_type;
	node->next = NULL;
	return (node);
}

void	free_token_stack(t_token *token_stack)
{
	t_token	*current;

	while (token_stack)
	{
		current = token_stack;
		token_stack = token_stack->next;
		free(current->value);
		free(current);
	}
}

void	print_token_stack(t_token *token_stack)
{
	t_token	*current;

	while (token_stack)
	{
		current = token_stack;
		ft_printf("Token Value: %s Token Type: %d \n",current->value, current->type);
		token_stack = token_stack->next;
	}
}
