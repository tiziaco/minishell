/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiacovel <tiacovel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 14:39:24 by tiacovel          #+#    #+#             */
/*   Updated: 2024/02/20 13:30:51 by tiacovel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/commands.h"

static void	free_env(char **envp)
{
	int	i;

	i = 0;
	while (!envp[i])
	{
		free(envp[i]);
		i++;
	}
	//free(envp);
}

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
			free_env(new_envp);
			return (NULL);
		}
		i++;
	}
	return (new_envp);
}

int	ft_export(char ***envp, const char *name, const char *value)
{
	char	**env;
	char	**new_envp;
	char	*env_var;
	int		env_size;

	if (name == NULL || value == NULL)
		return (-1);
	env_var = malloc(ft_strlen(name) + ft_strlen(value) + 2); // +2 for '=' and '\0'
	if (env_var == NULL)
		return (-1);
	ft_strcpy(env_var, (char *)name);
	ft_strcat(env_var, "=");
	ft_strcat(env_var, (char *)value);
	env = *envp;
	while (*env != NULL)
	{
		if ((ft_strncmp(*env, name, ft_strlen(name)) == 0) && 
			(*env)[ft_strlen(name)] == '=')
		{
			free(*env);
			*env = env_var;
			return (0);
		}
		env++;
	}
	// Variable does not exist, add it
	env_size = get_env_size(*envp);
	new_envp = copy_existing_environment(*envp, env_size);
	if (!new_envp)
	{
		free(env_var);
		return (-1);
	}
	new_envp[env_size] = env_var;
	new_envp[env_size + 1] = NULL;
	//free_env(*envp);
	*envp = new_envp;
	return (0);
}
