#include "so_long.h"

static t_map *allocate_map(int rows)
{
	t_map *map;

	map = ft_calloc(1, sizeof(t_map));
	if (!map)
		return (NULL);
	map->map_array = ft_calloc(rows + 1, sizeof(char *));
	if (!map->map_array)
	{
		free(map);
		return (NULL);
	}
	return (map);
}

void load_default_map(t_game *game)
{
	static char *def_map[] = {
		"1111111111111111",
		"1P0000C000000001",
		"1011011011110111",
		"100001000000C0E1",
		"1011110111110101",
		"1000C00000000001",
		"1011011011110111",
		"1C0001000000C001",
		"1111111111111111",
		NULL};

	t_map *map;
	int rows;
	int i;

	rows = 0;
	while (def_map[rows])
		rows++;
	map = allocate_map(rows);
	if (!map)
		return;
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
	game->map = map;
}
