#include "so_long.h"

/*
** find_player_pos:
**  If needed, we could find the P here,
**  but we already store it in check_chars_count().
**  We'll keep it as a fallback if we want to ensure it was found.
*/
static int find_player_pos(t_map *map_data, int *p_x, int *p_y)
{
    if (map_data->player_count != 1)
        return (ft_printf("Error\nNo valid player found.\n"), 0);
    *p_x = map_data->player_x;
    *p_y = map_data->player_y;
    return (1);
}

/*
** duplicate_map:
**  - Returns a fresh copy of map_array to manipulate in flood_fill.
*/
static char **duplicate_map(char **map_array, int height)
{
    char **copy;
    int i;

    copy = (char **)malloc(sizeof(char *) * (height + 1));
    if (!copy)
        return (NULL);
    i = 0;
    while (i < height)
    {
        copy[i] = ft_strdup(map_array[i]);
        if (!copy[i])
        {
            free_map(copy);
            return (NULL);
        }
        i++;
    }
    copy[i] = NULL;
    return (copy);
}

/*
** flood_fill:
**  - Mark reachable cells as 'X'.
**  - We'll skip walls and already 'X' cells.
**  - Recursively fill up/down/left/right.
*/
static void flood_fill(char **map_copy, int x, int y, t_map *map_data)
{
    if (y < 0 || x < 0 || y >= map_data->width || x >= map_data->height)
        return;
    if (map_copy[x][y] == '1' || map_copy[x][y] == 'X')
        return;
    map_copy[x][y] = 'X'; // Mark visited
    flood_fill(map_copy, x - 1, y, map_data);
    flood_fill(map_copy, x + 1, y, map_data);
    flood_fill(map_copy, x, y - 1, map_data);
    flood_fill(map_copy, x, y + 1, map_data);
}

/*
** verify_reachable:
**  - Check if all 'C' and 'E' in the original map are reachable
**    (i.e. turned into 'X' in the map_copy).
*/
static int verify_reachable(char **map_copy, t_map *map_data)
{
    int i;
    int j;

    i = 0;
    while (i < map_data->height)
    {
        j = 0;
        while (j < map_data->width)
        {
            if (map_data->map_array[i][j] == 'C' || map_data->map_array[i][j] == 'E')
            {
                if (map_copy[i][j] != 'X')
                    return (ft_printf("Error\nUnreachable C or E at (%d,%d).\n", i, j), 0);
            }
            j++;
        }
        i++;
    }
    return (1);
}

/*
** check_path:
**  - Finds player P coords.
**  - Duplicates the map.
**  - Flood fill from the player's position.
**  - Verify that all 'C' and 'E' are reachable.
*/
int check_path(t_map *map_data)
{
    char **map_copy;
    int p_x;
    int p_y;

    if (!find_player_pos(map_data, &p_x, &p_y))
        return (0);
    map_copy = duplicate_map(map_data->map_array, map_data->height);
    if (!map_copy)
        return (ft_printf("Error\nFailed to copy map.\n"), 0);
    flood_fill(map_copy, p_x, p_y, map_data);
    if (!verify_reachable(map_copy, map_data))
    {
        free_map(map_copy);
        return (0);
    }
    free_map(map_copy);
    return (1);
}
