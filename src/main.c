/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiacovel <tiacovel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 16:16:11 by tiacovel          #+#    #+#             */
/*   Updated: 2024/02/27 18:25:14 by tiacovel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/commands.h"

static int	check_args(t_data *data, int argc, char **argv)
{
	if (argc != 1 && argc != 3)
		return (sys_error(ARG_ERROR));
	if (argc == 3)
	{
		data->background_mode = false;
		if (!argv[1] || (argv[1] && ft_strcmp(argv[1], "-c") != 0))
			return (sys_error(ARG_ERROR));
		else if (!argv[2] || (argv[2] && argv[2][0] == '\0'))
			return (sys_error(ARG_ERROR));
	}
	else
		data->background_mode = true;
	return (true);
}

void	init_foreground_mode(t_data *data)
{
	int	exit_code;

	while (1)
	{
		/* set_signals_interactive();
		set_signals_noninteractive(); */
		data->line = readline(MSH_PROMPT);
		if (parse_input(data) == OP_SUCCESS)
			exit_code = execute_command(data);
		else
			exit_code = OP_FAIL;
		free_data(data, false);
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
		if (parse_user_input(data) == true)
			exit_code = execute_command(data);
		else
			exit_code = OP_FAIL;
		i++;
		free_data(data, false);
	}
	free_double_pointer(inputs);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	data = init_data(*envp);
	if (!data)
		return (EXIT_FAILURE);
	if (data->background_mode)
		init_background_mode(data, argv[2]);
	else
		init_foreground_mode(data);
	//exit_shell(&data, exit_code);
	return (0);
}
