/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 11:17:32 by lilefebv          #+#    #+#             */
/*   Updated: 2025/01/14 11:37:51 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	init_vars(int *i, int *is_valid)
{
	*i = 0;
	*is_valid = 1;
}

int	count_file_lines(char *map_name, t_map *map)
{
	char	*line;
	int		i;
	int		fd;
	int		is_valid;

	fd = open(map_name, O_RDONLY);
	if (fd == -1)
		return (print_error("invalid map name"), 0);
	init_vars(&i, &is_valid);
	line = get_next_line(fd);
	while (line)
	{
		map->length = ft_count_words(line, " \n");
		free(line);
		line = get_next_line(fd);
		if (line && ft_count_words(line, " \n") != (size_t)map->length
			&& ft_count_words(line, " \n") != 0)
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
	char	*have_color;
	int		y;

	splited = ft_split(line, " \n");
	if (!splited)
		return (free(line), 0);
	y = 0;
	while (splited[y])
	{
		map->map[i][y] = ft_atoi(splited[y]);
		if (map->map[i][y] > map->highest)
			map->highest = map->map[i][y];
		have_color = ft_strnstr(splited[y], ",0x", 15);
		if (have_color)
			map->color_map[i][y] = ft_atoi_base(
					ft_str_tolower(have_color + 3), "0123456789abcdef");
		if (have_color)
			map->have_color = 1;
		else
			map->color_map[i][y] = 0xffffff;
		y++;
	}
	ft_free_tab(splited, ft_count_words(line, " \n"));
	return (free(line), 1);
}

int	malloc_line_map(t_map *map, int i)
{
	map->map[i] = calloc(sizeof(int), map->length);
	if (!map->map[i])
		return (ft_free_tab_int(map->map, i),
			ft_free_tab_int(map->color_map, i), 0);
	map->color_map[i] = calloc(sizeof(int), map->length);
	if (!map->color_map[i])
		return (ft_free_tab_int(map->map, i + 1),
			ft_free_tab_int(map->color_map, i), 0);
	return (1);
}
