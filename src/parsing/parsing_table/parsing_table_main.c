/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_table_main.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 15:32:49 by jkaller           #+#    #+#             */
/*   Updated: 2024/03/02 23:27:42 by jkaller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minish.h"
#include "../../../include/parsing.h"
#include "../../../include/libft.h"
#include <unistd.h>
#include <fcntl.h>

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

int	fill_table(int fd, t_table *parsing_table)
{
	int		row;
	char	*line;
	char	**row_values;

	row = 0;
	while (row <= PARSING_TABLE_LENGTH)
	{
		line = get_next_line(fd);
		if (line == 0)
			return (0);
		row_values = ft_split(line, '\t');
		if (row_values == 0)
			return (0);
		free(line);
		fill_row(row_values, parsing_table + row);
		free_row(row_values);
		row++;
	}
	line = NULL;
	row_values = NULL;
	return (1);
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
