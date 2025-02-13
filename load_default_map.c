#include "so_long.h"

/*
** load_default_map:
**  - Loads a default map with 2 monsters placed correctly.
**  - Ensures they start on empty ground (not walls).
*/
void load_default_map(t_game *game)
{
	static char *def_map[] = {
		"11111111111111111111",
		"1P0000C00000000000E1",
		"10110110111101111101",
		"100001000000C0000001",
		"10111101111101111101",
		"1000C000000000000001",
		"10110110111101111101",
		"1C0001000000C0000001",
		"10111101101110111001",
		"100000000M0000000001",
		"10110111111101110101",
		"1M000100000000000001",
		"10111101101110111001",
		"10000000000000000001",
		"11111111111111111111",
		NULL};

	t_map *map;
	int rows;
	int i;

	rows = 0;
	while (def_map[rows])
		rows++;
	map = ft_calloc(1, sizeof(t_map));
	if (!map)
		return;
	map->map_array = ft_calloc(rows + 1, sizeof(char *));
	if (!map->map_array)
	{
		free(map);
		return;
	}
	i = 0;
	while (i < rows)
	{
		map->map_array[i] = ft_strdup(def_map[i]);
		if (!map->map_array[i++])
		{
			free_map(map->map_array);
			free(map);
			return;
		}
	}
	map->height = rows;
	map->width = ft_strlen(def_map[0]);
	map->player_lives = 3; // Set player lives
	game->map = map;
}
