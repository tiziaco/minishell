/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiacovel <tiacovel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 14:39:24 by tiacovel          #+#    #+#             */
/*   Updated: 2024/03/26 11:37:27 by tiacovel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/commands.h"

static bool	check_key_name(char *var)
{
	int	i;

	i = 0;
	while (var[i] && var[i] != '=')
	{
		if (ft_isalnum(var[i]) == 0 && var[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

static char	**get_key_val(char *arg)
{
	char	**key_val;

	key_val = ft_split(arg, '=');
	return (key_val);
}

int	ft_export(t_data *data, char **args)
{
	int		i;
	int		status;
	char	**key_val;

	i = 1;
	while (args[i] != NULL)
	{
		if (!check_key_name(args[i]))
			return (cmd_error(INVALID_KEY));
		if (ft_strchr(args[i], '=') == NULL)
			return (cmd_error(INVALID_PARM));
		key_val = get_key_val(args[i]);
		if (set_var(data, key_val[0], key_val[1]) != EXIT_SUCCESS)
		{
			free_double_pointer(key_val);
			return (EXIT_FAILURE);
		}
		free_double_pointer(key_val);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	ft_unset(t_data *data, char **args)
{
	int	i;
	int	key_index;

	i = 1;
	while (args[i] != NULL)
	{
		if (!check_key_name(args[i]))
			return (cmd_error(INVALID_KEY));
		key_index = search_key(data->envp, args[i]);
		if (key_index > 0)
			remove_var(data, key_index);
		i++;
	}
	return (EXIT_SUCCESS);
}
