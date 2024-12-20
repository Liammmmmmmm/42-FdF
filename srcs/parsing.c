/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 10:42:51 by lilefebv          #+#    #+#             */
/*   Updated: 2024/12/20 13:53:36 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	count_file_lines(char *map_name, t_map *map)
{
	char	*line;
	int		i;
	int		fd;
	int		is_valid;

	fd = open(map_name, O_RDONLY);
	if (fd == -1)
		return (print_error("invalid map name"), 0);
	i = 0;
	is_valid == 1;
	line = get_next_line(fd);
	while (line)
	{
		map->length = ft_count_words(line, " \n");
		free(line);
		line = get_next_line(fd);
		if (line && ft_count_words(line, " \n") != map->length && ft_count_words(line, " \n") != 0)
			is_valid = 0;
		i++;
	}
	close(fd);
	if (!is_valid)
		return (print_error("invalid map, verify lines length"), 0);
	map->height = i;
	return (1);
}

int	fill_line(char *line, t_map *map, int i)
{
	char	**splited;
	int		y;
	
	splited = ft_split(line, " \n");
	if (!splited)
		return (free(line), 0);
	y = 0;
	while (splited[y])
	{
		map->map[i][y] = ft_atoi(splited[y]);
		y++;
	}
	ft_free_tab(splited, ft_count_words(line, " \n"));
	return (free(line), 1);
}

int	init_map_values(char *map_name, t_map *map)
{
	char	*line;
	int		fd;
	int		i;

	fd = open(map_name, O_RDONLY);
	if (fd == -1)
		return (print_error("error opening file"), 0);
	map->map = malloc(sizeof(int*) * map->height);
	line = get_next_line(fd);
	i = 0;
	while (line)
	{
		// ajouter la gestion des couleurs
		
		line = get_next_line(fd);
		i++;
	}
	close(fd);
	return (1);
}

int	is_valid_file_extension(char *map_name)
{
	int	len;

	len = ft_strlen(map_name);
	if (len <= 4)
		return (print_error("invalid map extension"), 0);
	if (map_name[len - 4] == '.' && map_name[len - 3] == 'f'
		&& map_name[len - 2] == 'd' && map_name[len - 1] == 'f')
		return (1);
	return (print_error("invalid map extension"), 0);
}

t_map	*parse_map(char	*map_name)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	if (!map)
		return (print_error("malloc failed"), NULL);
	if (is_valid_file_extension(map_name) == 0)
		return (free(map), NULL);
	map->length = 0;
	if (count_file_lines(map_name, map) == 0)
		return (free(map), NULL);
	
	return (map);
}
