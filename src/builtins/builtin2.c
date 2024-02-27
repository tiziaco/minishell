/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiacovel <tiacovel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 14:39:24 by tiacovel          #+#    #+#             */
/*   Updated: 2024/02/27 11:46:19 by tiacovel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/commands.h"

static int	get_env_size(char **envp)
{
	int		env_size;
	char	**curr_env;

	env_size = 0;
	curr_env = envp;
	while (*curr_env != NULL)
	{
		env_size++;
		curr_env++;
	}
	return (env_size);
}

static char	**copy_existing_environment(char **envp, int env_size)
{
	char	**new_envp;
	int		i;

	new_envp = (char **)malloc(sizeof(char *) * (env_size + 2)); // +2 for new variable and NULL terminator
	if (new_envp == NULL) 
		return (NULL);
	i = 0;
	while (i < env_size)
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

static int	searc_and_replace(char *env_var, char *name, char ***envp)
{
	char	**env;

	env = *envp;
	while (*env != NULL)
	{
		if ((ft_strncmp(*env, name, ft_strlen(name)) == 0) && 
			(*env)[ft_strlen(name)] == '=')
		{
			free(*env);
			*env = env_var;
			return (OP_SUCCESS);
		}
		env++;
	}
	return (OP_FAIL);
}

static int	add_new_var(char *env_var, char ***envp)
{
	int		env_size;
	char	**new_envp;

	env_size = get_env_size(*envp);
	new_envp = copy_existing_environment(*envp, env_size);
	if (!new_envp)
	{
		free(env_var);
		return (OP_FAIL);
	}
	new_envp[env_size] = env_var;
	new_envp[env_size + 1] = NULL;
	*envp = new_envp;
	return(OP_SUCCESS);
}

int	ft_export(char ***envp, const char *name, const char *value)
{
	char	*env_var;
	int		status;

	if (name == NULL || value == NULL)
		return (-1);
	env_var = malloc(ft_strlen(name) + ft_strlen(value) + 2);
	if (env_var == NULL)
		return (-1);
	ft_strcpy(env_var, (char *)name);
	ft_strcat(env_var, "=");
	ft_strcat(env_var, (char *)value);
	if (searc_and_replace(env_var, name, envp) == OP_SUCCESS)
	{
		free(env_var);
		return (OP_SUCCESS);
	}
	status = add_new_var(env_var, envp);
	return (status);
}
