/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 10:42:51 by lilefebv          #+#    #+#             */
/*   Updated: 2025/01/14 11:21:02 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	init_map_values(char *map_name, t_map *map)
{
	char	*line;
	int		fd;
	int		i;

	fd = open(map_name, O_RDONLY);
	if (fd == -1)
		return (print_error("error opening file"), 0);
	map->map = malloc(sizeof(int *) * map->height);
	map->color_map = malloc(sizeof(int *) * map->height);
	if (!map->map || !map->color_map)
		return (free(map->map), free(map->color_map), 0);
	line = get_next_line(fd);
	i = 0;
	while (line)
	{
		if (malloc_line_map(map, i) == 0)
			return (0);
		if (fill_line(line, map, i) == 0)
			return (ft_free_tab_int(map->map, i),
				ft_free_tab_int(map->color_map, i), 0);
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
	map->have_color = 0;
	map->highest = -2147483648;
	if (init_map_values(map_name, map) == 0)
		return (free(map), NULL);
	return (map);
}
