/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiacovel <tiacovel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:30:21 by tiacovel          #+#    #+#             */
/*   Updated: 2024/03/06 17:19:16 by tiacovel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minish.h"

char	**copy_environment(char **envp, int env_size)
{
	char	**new_envp;
	int		i;

	new_envp = (char **)malloc(sizeof(char *) * (env_size + 1));
	if (new_envp == NULL) 
		return (NULL);
	i = 0;
	while (envp[i] && i < env_size)
	{
		new_envp[i] = ft_strdup(envp[i]);
		if (new_envp[i] == NULL)
		{
			free_double_pointer(new_envp);
			return (NULL);
		}
		i++;
	}
	return (new_envp);
}

int	set_var(t_data *data, char *key, char *val)
{
	int		env_size;
	int		key_index;
	char	*env_var;
	char	**new_envp;

	env_var = get_env_var(key, val);
	key_index = search_key(data->envp, key);
	if (key_index < 0)
	{
		env_size = get_env_size(data->envp);
		data->envp = copy_environment(data->envp, env_size + 1);
		if (!data->envp)
		{
			free_pointer(env_var);
			return (sys_error(MEM_ERROR));
		}
		data->envp[env_size] = ft_strdup(env_var);
	}
	else
	{
		free_pointer(data->envp[key_index]);
		data->envp[key_index] = ft_strdup(env_var);
	}
	free_pointer(env_var);
	return (OP_SUCCESS);
}

int	remove_var(t_data *data, int key_index)
{
	int	i;
	int	size;

	if (key_index > get_env_size(data->envp))
		return (cmd_error(INVALID_KEY));
	free_pointer(data->envp[key_index]);
	i = key_index;
	size = key_index;
	while (data->envp[i + 1])
	{
		data->envp[i] = ft_strdup(data->envp[i + 1]);
		free_pointer(data->envp[i + 1]);
		size++;
		i++;
	}
	data->envp = copy_environment(data->envp, size);
	if (!data->envp)
		return (sys_error(MEM_ERROR));
	return (OP_SUCCESS);
}
