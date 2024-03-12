/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parsing_table.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 15:32:49 by jkaller           #+#    #+#             */
/*   Updated: 2024/03/12 14:01:36 by jkaller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minish.h"
#include "../../include/parser.h"
#include "../../include/libft.h"

int	get_table_length(char *table_path)
{
	int		table_length;
	int		fd;
	char	*line;

	table_length = 0;
	fd = open(table_path, O_RDWR);
	if (fd == -1)
		return (0);
	while (1)
	{
		line = get_next_line(fd);
		if (line == 0)
		{
			free(line);
			line = NULL;
			close(fd);
			return (table_length);
		}
		table_length++;
	}	
}


void	free_row(char **row_values)
{
	char	**temp;

	temp = row_values;
	while (*row_values != NULL)
	{
		free(*row_values);
		row_values++;
	}
	free(temp);
}

void	fill_row(char **row_values, t_table *parsing_table)
{
	(*parsing_table).state = ft_atoi(row_values[0]);
	(*parsing_table).token_grammar_type = ft_atoi(row_values[1]);
	(*parsing_table).action = ft_atoi(row_values[2]);
	(*parsing_table).next_state = ft_atoi(row_values[3]);
	(*parsing_table).reduced_token = ft_atoi(row_values[4]);
}

int	fill_table(int fd, t_table *parsing_table, int table_length)
{
	int		row;
	char	*line;
	char	**row_values;

	row = 0;
	while (row <= table_length)
	{
		line = get_next_line(fd);
		if (line == 0)
			return (EXIT_FAILURE);
		row_values = ft_split(line, '\t');
		if (row_values == 0)
			return (EXIT_FAILURE);
		free(line);
		fill_row(row_values, parsing_table + row);
		free_row(row_values);
		row++;
	}
	line = NULL;
	row_values = NULL;
	return (EXIT_SUCCESS);
}

t_table	*init_parsing_table(t_data *data)
{
	int		fd;
	t_table	*parsing_table;
	char	*table_path;

	table_path = data->main_path;
	table_path = ft_strcat(table_path, PARSING_TABLE_PATH);
	data->table_length = get_table_length(table_path);
	parsing_table = (t_table *)ft_calloc(sizeof(t_table), data->table_length);
	if (!parsing_table)
		return (NULL);
	fd = open(table_path, O_RDWR);
	if (fd == -1)
		return (NULL);
	fill_table(fd, parsing_table, data->table_length);
	close(fd);
	return (parsing_table);
}
