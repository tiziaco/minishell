/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_outils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiacovel <tiacovel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:26:51 by tiacovel          #+#    #+#             */
/*   Updated: 2024/02/28 16:31:53 by tiacovel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minish.h"

int	get_env_size(char **envp)
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

int	search_key(char ***envp, char *key)
{
	int i;

	while (*envp[i] != NULL)
	{
		if ((ft_strncmp(*envp[i], key, ft_strlen(key)) == 0)
			&& *envp[i][ft_strlen(key)] == '=')
			return (i);
		i++;
	}
	return (-1);
}

char	*get_env_var(char *key, char *val)
{
    char    *env_var;

	env_var = malloc(ft_strlen(key) + ft_strlen(val) + 2);
	if (env_var == NULL)
		return (NULL);
    if (val == NULL)
		val = "";
	ft_strcpy(env_var, key);
	ft_strcat(env_var, "=");
	ft_strcat(env_var, val);
    return (env_var);
}