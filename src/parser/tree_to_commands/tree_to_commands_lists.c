/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_to_commands_lists.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 17:51:01 by jkaller           #+#    #+#             */
/*   Updated: 2024/03/20 19:56:28 by jkaller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minish.h"
#include "../../../include/parser.h"
#include "../../../include/libft.h"
#include <unistd.h>

void	ft_cmdadd_back(t_cmd **lst, t_cmd *new)
{
	t_cmd	*last;
	t_cmd	*previous;

	previous = NULL;
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
	new->prev = last;
}

void	ft_redirectadd_back(t_redirect **lst, t_redirect *new)
{
	t_redirect	*last;
	t_redirect	*previous;

	previous = NULL;
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
	new->prev = last;
}

t_redirect	*ft_lstnew_redirect(int redirect)
{
	t_redirect	*node;

	node = (t_redirect *)calloc(sizeof(t_redirect), 1);
	node->redirect = redirect;
	if (!node)
		return (NULL);
	return (node);
}