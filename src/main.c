/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 16:16:11 by tiacovel          #+#    #+#             */
/*   Updated: 2024/03/07 16:40:44 by jkaller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/commands.h"

static int	check_args(t_data *data, int argc, char **argv)
{
	if (argc != 1 && argc != 3)
		return (sys_error(ARG_ERROR));
	if (argc == 3)
	{
		data->background_mode = true;
		if (!argv[1] || (argv[1] && ft_strcmp(argv[1], "-c") != 0))
			return (sys_error(ARG_ERROR));
		else if (!argv[2] || (argv[2] && argv[2][0] == '\0'))
			return (sys_error(ARG_ERROR));
	}
	else
		data->background_mode = false;
	return (OP_SUCCESS);
}

void	init_foreground_mode(t_data *data)
{
	int	exit_code;

	init_signals(data);
	while (1)
	{
		data->line = readline(MSH_PROMPT);
		if (data->line == NULL)
			break;
		if (data->line && data->line[0])
			add_history(data->line);
		if (mini_parse_input(data) == OP_SUCCESS)
		{
			parse_input(data); //this should replace mini_parse_input
			exit_code = execute_command(data);
		}
		else
			exit_code = OP_FAIL;
		//free_data(data, false);
	}
}

void	init_background_mode(t_data	*data, char *arg)
{
	char	**inputs;
	int		exit_code;
	int		i;

	inputs = ft_split(arg, ';');
	if (!inputs)
		exit_shell(data, EXIT_FAILURE);
	i = 0;
	while (inputs[i])
	{
		data->line = ft_strdup(inputs[i]);
		if (mini_parse_input(data) == OP_SUCCESS)
			exit_code = execute_command(data);
		else
			exit_code = OP_FAIL;
		i++;
		//free_data(data, false);
	}
	free_double_pointer(inputs);
}

// int	main(int argc, char **argv, char **envp)
// {
// 	t_data	*data;

// 	data = init_data(envp);
// 	if (!data)
// 		return (EXIT_FAILURE);
// 	check_args(data, argc, argv);
// 	if (data->background_mode)
// 		init_background_mode(data, argv[2]);
// 	else
// 		init_foreground_mode(data);
// 	exit_shell(data, EXIT_SUCCESS);
// 	return (0);
// }

t_data	*init(t_data *data, char *str)
{
	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!data->cmd)
		return (NULL);
	data->envp = NULL;
	data->cmd = NULL;
	data->line =ft_strdup(str);
	return (data);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	data = init(data, argv[1]);
	parse_input(data);
}


/* TEST main for background mode */

/* int	main(int _, char **__, char **envp)
{
	t_data	*data;
	int		argc = 3;
	char	*argv[4] = {argv[0] = "minishell\0", argv[1] = "-c", argv[2] = "pwd", argv[3] = NULL};

	data = init_data(envp);
	if (!data)
		return (EXIT_FAILURE);
	check_args(data, argc, argv);
	if (data->background_mode)
		init_background_mode(data, argv[2]);
	else
		init_foreground_mode(data);
	exit_shell(data, EXIT_SUCCESS);
	return (0);
} */