/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_table_handler.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 15:32:49 by jkaller           #+#    #+#             */
/*   Updated: 2024/02/23 18:45:37 by jkaller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minish.h"
#include "../../../include/parsing.h"
#include "../../../include/libft.h"
#include <unistd.h>
#include <fcntl.h>

void	fill_row(char **row_values, t_table *parsing_table)
{
	(*parsing_table).state = ft_atoi(row_values[0]);
	ft_printf("state: %i\n", (*parsing_table).state);
	(*parsing_table).token_grammar_type = ft_atoi(row_values[1]);
	ft_printf("token_grammar_type: %i\n", (*parsing_table).token_grammar_type);
	(*parsing_table).action = ft_atoi(row_values[2]);
	ft_printf("action: %i\n", (*parsing_table).action);
	(*parsing_table).next_state = ft_atoi(row_values[3]);
	ft_printf("next_state: %i\n", (*parsing_table).next_state);
	(*parsing_table).reduced_token = ft_atoi(row_values[4]);
	ft_printf("reduced_token: %i\n", (*parsing_table).reduced_token);
}

void	fill_table(int fd, t_table *parsing_table)
{
	int		row;
	char	*line;
	char	**row_values;

	row = 0;
	while (row < PARSING_TABLE_LENGTH)
	{
		line = get_next_line(fd);
		if (line == 0)
			break ;
		row_values = ft_split(line, '\t');
		free(line);
		if (row_values == 0)
			break ;
		parsing_table = (t_table *)malloc(sizeof(t_table));
		if (parsing_table == NULL)
		{
			free(line);
			free(row_values);
			break ;
		}
		fill_row(row_values, parsing_table + row);
		free(row_values);
		row++;
	}
}

void	initialise_table(t_table *parsing_table)
{
	parsing_table->state = 0;
	parsing_table->token_grammar_type = 0;
	parsing_table->action = 0;
	parsing_table->next_state = 0;
	parsing_table->reduced_token = 0;
}

void	parse_table(char *path, t_table *parsing_table)
{
	int		fd;

	initialise_table(parsing_table);
	fd = open(path, O_RDWR);
	if (fd == -1)
		ft_printf("Error opening the file!!");
	fill_table(fd, parsing_table);
	close(fd);
}


	// 	ft_printf("row values in loop %i\n", ft_atoi(row_values[0]));
	// 	ft_printf("row values in loop %i\n", ft_atoi(row_values[1]));
	// 	ft_printf("row values in loop %i\n", ft_atoi(row_values[2]));
	// 	ft_printf("row values in loop %i\n", ft_atoi(row_values[3]));
	// 	ft_printf("row values in loop %i\n", ft_atoi(row_values[4]));