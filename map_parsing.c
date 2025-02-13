#include "so_long.h"

/*
** copy_old_map:
** Helper to expand your map array by 1 line each time you read a new line.
*/
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

/*
** read_map_file:
**  - Opens the file, reads line by line using get_next_line().
**  - Stores lines into a newly allocated char**.
**  - Returns the final NULL-terminated char** or NULL on error.
*/
char **read_map_file(char *filename)
{
    int fd;
    int count;
    char *line;
    char **map;
    char **temp;

    fd = open(filename, O_RDONLY);
    if (fd < 0)
    {
        ft_printf("Error\nFailed to open file: %s\n", filename);
        return (NULL);
    }
    map = NULL;
    count = 0;
    line = get_next_line(fd);
    while (line)
    {
        temp = map;
        map = (char **)malloc(sizeof(char *) * (count + 2));
        if (!map)
        {
            free_map(temp);
            close(fd);
            ft_printf("Error\nmalloc failed in read_map_file().\n");
            return (NULL);
        }
        copy_old_map(temp, map, count);
        map[count] = line; // line includes its '\n'
        map[count + 1] = NULL;
        count++;
        free(temp); // free old pointer (not its contents)
        line = get_next_line(fd);
    }
    close(fd);
    return (map);
}

/*
** free_map:
**  - Frees all strings and then the char** itself.
*/
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

/*
** parse_map:
**  - Allocate t_map, read file into map_array, set width/height.
**  - Return 1 on success, 0 on error.
*/
int parse_map(t_game *game, char *filename)
{
    game->map = (t_map *)ft_calloc(1, sizeof(t_map));
    if (!game->map)
    {
        ft_printf("Error\nFailed to allocate t_map.\n");
        return (0);
    }
    game->map->map_array = read_map_file(filename);
    if (!game->map->map_array)
    {
        free(game->map);
        game->map = NULL;
        return (0);
    }

    // Prevent memory leak by checking before returning
    game->map->height = 0;
    while (game->map->map_array[game->map->height])
        game->map->height++;

    if (game->map->height > 0)
        game->map->width = ft_strlen(game->map->map_array[0]);

    // Check for empty map
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
