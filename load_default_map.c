/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_default_map.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anebbou <anebbou@student42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 10:00:00 by anebbou           #+#    #+#             */
/*   Updated: 2025/02/19 17:35:32 by anebbou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static char	**allocate_and_copy_map(char *filename, int *rows)
{
	char	**map_array;
	int		fd;
	char	*line;
	char	**temp;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("Error: Failed to open file %s\n", filename);
		return (NULL);
	}
	map_array = NULL;
	*rows = 0;
	line = get_next_line(fd);
	while (line)
	{
		temp = realloc(map_array, sizeof(char *) * (*rows + 2));
		if (!temp)
		{
			ft_printf("Error: Failed to allocate memory for map array\n");
			free(map_array);
			close(fd);
			return (NULL);
		}
		map_array = temp;
		map_array[*rows] = line;
		(*rows)++;
		map_array[*rows] = NULL;
		line = get_next_line(fd);
	}
	close(fd);
	return (map_array);
}

void	load_default_map(t_game *game)
{
	t_map	*map;
	int		rows;

	map = ft_calloc(1, sizeof(t_map));
	if (!map)
	{
		ft_printf("Error: Failed to allocate memory for map struct\n");
		return ;
	}
	map->map_array = allocate_and_copy_map("maps/default_map.ber", &rows);
	if (!map->map_array)
	{
		ft_printf("Error: Failed to allocate and copy map\n");
		free(map);
		return ;
	}
	map->height = rows;
	map->width = ft_strlen(map->map_array[0]);
	map->player_lives = 3;
	map->spawn_x = 1;
	map->spawn_y = 1;
	game->map = map;
}
