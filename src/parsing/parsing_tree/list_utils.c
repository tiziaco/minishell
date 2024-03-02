/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 19:16:06 by jkaller           #+#    #+#             */
/*   Updated: 2024/03/02 00:02:24 by jkaller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minish.h"
#include "../../../include/parsing.h"
#include "../../../include/libft.h"
#include <unistd.h>

void	subtree_add_back(t_tree_stack **subtree, t_tree_stack *tree_stack)
{
	t_tree_stack	*first;

	if (!*subtree)
		*subtree = tree_stack;
	else
	{
		first = *subtree;
		while ((*subtree)->next)
			*subtree = (*subtree)->next;
		(*subtree)->next = tree_stack;
		*subtree = first;
	}
	tree_stack->next = NULL;
}
