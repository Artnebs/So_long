#include "so_long.h"

/* Copy the old map pointers into the newly allocated array */
static void copy_old_map(char **old_map, char **new_map, int count)
{
	int i;

	i = 0;
	while (i < count)
	{
		new_map[i] = old_map[i];
		i++;
	}
}

/* Read a map file line by line into a NULL-terminated char** */
char **read_map_file(char *filename)
{
	int fd;
	int count;
	char *line;
	char **map;
	char **temp;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (ft_printf("Error\nFailed to open file: %s\n", filename), NULL);
	map = NULL;
	count = 0;
	line = get_next_line(fd);
	while (line)
	{
		temp = map;
		map = malloc(sizeof(char *) * (count + 2));
		if (!map)
		{
			free_map(temp);
			close(fd);
			return (ft_printf("Error\nmalloc failed.\n"), NULL);
		}
		copy_old_map(temp, map, count);
		map[count] = line;
		map[count + 1] = NULL;
		count++;
		free(temp);
		line = get_next_line(fd);
	}
	close(fd);
	return (map);
}

/* Free a map array */
void free_map(char **map_array)
{
	int i;

	if (!map_array)
		return;
	i = 0;
	while (map_array[i])
	{
		free(map_array[i]);
		i++;
	}
	free(map_array);
}

/* Parse the map from filename into game->map->map_array, set height/width */
int parse_map(t_game *game, char *filename)
{
	game->map = ft_calloc(1, sizeof(t_map));
	if (!game->map)
		return (ft_printf("Error\nFailed to allocate t_map.\n"), 0);

	game->map->map_array = read_map_file(filename);
	if (!game->map->map_array)
	{
		free(game->map);
		game->map = NULL;
		return (0);
	}
	game->map->height = 0;
	while (game->map->map_array[game->map->height])
		game->map->height++;
	if (game->map->height > 0)
		game->map->width = ft_strlen(game->map->map_array[0]);
	if (game->map->height == 0 || game->map->width == 0)
	{
		ft_printf("Error\nEmpty map.\n");
		free_map(game->map->map_array);
		free(game->map);
		game->map = NULL;
		return (0);
	}
	return (1);
}
