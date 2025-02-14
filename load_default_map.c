#include "so_long.h"

/* Local helper: read default_map.ber and store in map_array */
static char **allocate_and_copy_map(char *filename, int *rows)
{
	char **map_array;
	int fd;
	char *line;

	ft_printf("DEBUG: Opening file %s\n", filename);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("Error: Failed to open file %s\n", filename);
		return (NULL);
	}
	map_array = NULL;
	*rows = 0;

	while ((line = get_next_line(fd)))
	{
		char **temp = realloc(map_array, sizeof(char *) * (*rows + 2));
		if (!temp)
		{
			ft_printf("Error: Failed to allocate memory for map array\n");
			free(map_array);
			close(fd);
			return NULL;
		}
		map_array = temp;
		map_array[*rows] = line;
		(*rows)++;
		map_array[*rows] = NULL;
	}
	close(fd);
	ft_printf("DEBUG: File %s read successfully\n", filename);
	return (map_array);
}

/*
** load_default_map:
**  - Loads a larger default map with monsters (M).
**  - Player has 3 lives (map->player_lives = 3).
*/
void load_default_map(t_game *game)
{
	t_map *map;
	int rows;

	ft_printf("DEBUG: Loading default map\n");
	map = ft_calloc(1, sizeof(t_map));
	if (!map)
	{
		ft_printf("Error: Failed to allocate memory for map struct\n");
		return;
	}
	map->map_array = allocate_and_copy_map("maps/default_map.ber", &rows);
	if (!map->map_array)
	{
		ft_printf("Error: Failed to allocate and copy map\n");
		return (free(map), (void)0);
	}
	map->height = rows;
	map->width = ft_strlen(map->map_array[0]);
	map->player_lives = 3;
	map->spawn_x = 1;
	map->spawn_y = 1;
	game->map = map;
	ft_printf("DEBUG: Default map loaded successfully\n");
}
