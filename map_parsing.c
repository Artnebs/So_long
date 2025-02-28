/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anebbou <anebbou@student42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 10:00:00 by anebbou           #+#    #+#             */
/*   Updated: 2025/02/28 13:17:13 by anebbou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	copy_old_map(char **old_map, char **new_map, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		new_map[i] = old_map[i];
		i++;
	}
}

static char	**allocate_and_copy_map(char **map, char **temp,
									int count, char *line)
{
	map = malloc(sizeof(char *) * (count + 2));
	if (!map)
	{
		free_map(temp);
		return (NULL);
	}
	copy_old_map(temp, map, count);
	map[count] = line;
	map[count + 1] = NULL;
	free(temp);
	return (map);
}

char	**read_map_file(char *filename)
{
	int		fd;
	int		count;
	char	*line;
	char	**map;
	char	**temp;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	map = NULL;
	count = 0;
	line = get_next_line(fd);
	while (line)
	{
		temp = map;
		map = allocate_and_copy_map(map, temp, count, line);
		if (!map)
			return (close(fd), NULL);
		count++;
		line = get_next_line(fd);
	}
	close(fd);
	return (map);
}

static int	set_map_dimensions(t_game *game)
{
	game->map->height = 0;
	while (game->map->map_array[game->map->height])
		game->map->height++;
	if (game->map->height > 0)
		game->map->width = ft_strlen(game->map->map_array[0]);
	if (game->map->height == 0 || game->map->width == 0)
	{
		free_map(game->map->map_array);
		free(game->map);
		game->map = NULL;
		return (0);
	}
	return (1);
}

int	parse_map(t_game *game, char *filename)
{
	game->map = ft_calloc(1, sizeof(t_map));
	if (!game->map)
		return (0);
	game->map->map_array = read_map_file(filename);
	if (!game->map->map_array)
	{
		free(game->map);
		game->map = NULL;
		return (0);
	}
	return (set_map_dimensions(game));
}
