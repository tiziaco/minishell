/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiacovel <tiacovel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 12:50:51 by tiacovel          #+#    #+#             */
/*   Updated: 2024/03/14 13:25:55 by tiacovel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/commands.h"
#include <string.h>

static char	*concat_full_path(char *directory, char *command)
{
	char	*full_path;

	full_path = malloc(ft_strlen(directory) + ft_strlen(command) + 2);
	if (!full_path)
		return (NULL);
	ft_strcpy(full_path, directory);
	ft_strcat(full_path, "/");
	ft_strcat(full_path, command);
	return (full_path);
}

static char	*get_command_path(char **directories, char *command)
{
	DIR				*dir;
	char			*full_path;
	struct dirent	*entry;

	while (*directories != NULL)
	{
		dir = opendir(*directories);
		if (dir != NULL)
		{
			entry = readdir(dir);
			while (entry != NULL)
			{
				if (ft_strcmp(entry->d_name, command) == 0)
				{
					full_path = concat_full_path(*directories, command);
					closedir(dir);
					return (full_path);
				}
				entry = readdir(dir);
			}
			closedir(dir);
		}
		directories++;
	}
	return (NULL);
}

char	*search_command(char *command)
{
	char	*path_env;
	char	*path;
	char	*command_path;
	char	**directories;

	path_env = getenv("PATH");
	if (path_env == NULL)
	{
		perror("Unable to get PATH environment variable\n");
		return (NULL);
	}
	path = ft_strdup(path_env);
	if (path == NULL)
	{
		perror("Duplication failed");
		return (NULL);
	}
	directories = ft_split(path, ':');
	command_path = get_command_path(directories, command);
	free_double_pointer(directories);
	free(path);
	return (command_path);
}

int	exec_bin(t_data *data)
{
	char	*command_path;
	int		status;

	command_path = search_command(data->cmd->command);
	if (command_path == NULL)
		return (cmd_error(CMD_NOT_FOUND));
	//execve(command_path, data->cmd->args, data->envp);
	if (execve(command_path, data->cmd->args, data->envp))
	{
		free(command_path);
		exit(EXIT_FAILURE);
	}
	free(command_path);
	return (EXIT_SUCCESS);
}
