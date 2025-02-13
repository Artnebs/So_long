#include "so_long.h"

/*
** fill_map_dimensions:
**  - Removes trailing '\n' if present.
**  - Sets map_data->height and map_data->width accordingly.
** Return 1 if okay, 0 if empty map.
*/
static int fill_map_dimensions(t_map *map_data)
{
    int i;
    int len;

    i = 0;
    while (map_data->map_array && map_data->map_array[i])
    {
        len = ft_strlen(map_data->map_array[i]);
        // Remove trailing newline if present
        if (len > 0 && map_data->map_array[i][len - 1] == '\n')
            map_data->map_array[i][len - 1] = '\0';
        i++;
    }
    map_data->height = i;
    if (map_data->height == 0)
        return (ft_printf("Error\nEmpty map.\n"), 0);
    map_data->width = ft_strlen(map_data->map_array[0]);
    return (1);
}

/*
** check_rectangle:
**  - Checks that all lines have the same width.
*/
int check_rectangle(t_map *map_data)
{
    int i;
    int first_width;

    first_width = map_data->width;
    i = 0;
    while (map_data->map_array[i])
    {
        if ((int)ft_strlen(map_data->map_array[i]) != first_width)
            return (ft_printf("Error\nMap is not rectangular.\n"), 0);
        i++;
    }
    return (1);
}

/*
** check_walls:
**  - Ensures first/last row are all '1'.
**  - Ensures first/last column are all '1'.
*/
int check_walls(t_map *map_data)
{
    int i;
    int last_row;

    last_row = map_data->height - 1;
    i = 0;
    // Top and bottom row
    while (i < map_data->width)
    {
        if (map_data->map_array[0][i] != '1' || map_data->map_array[last_row][i] != '1')
            return (ft_printf("Error\nMissing top/bottom walls.\n"), 0);
        i++;
    }
    // Left and right column
    i = 0;
    while (i < map_data->height)
    {
        if (map_data->map_array[i][0] != '1' || map_data->map_array[i][map_data->width - 1] != '1')
            return (ft_printf("Error\nMissing side walls.\n"), 0);
        i++;
    }
    return (1);
}

/*
** check_chars_count:
**  - Ensure exactly 1 player P, at least 1 exit E, at least 1 collect C.
**  - Check for invalid characters (other than 0,1,P,E,C,M).
*/
int check_chars_count(t_map *map_data)
{
    int i;
    int j;
    char c;

    i = 0;
    while (i < map_data->height)
    {
        j = 0;
        while (j < map_data->width)
        {
            c = map_data->map_array[i][j];
            if (c == 'P')
            {
                map_data->player_count++;
                map_data->player_x = i;
                map_data->player_y = j;
            }
            else if (c == 'E')
                map_data->exit_count++;
            else if (c == 'C')
                map_data->collect_count++;
            else if (c != '0' && c != '1' && c != 'M' && c != '\0')
                return (ft_printf("Error\nInvalid char '%c' in map.\n", c), 0);
            j++;
        }
        i++;
    }
    if (map_data->player_count != 1 || map_data->exit_count < 1 || map_data->collect_count < 1)
        return (ft_printf("Error\nNeed 1P, >=1E, >=1C.\n"), 0);
    return (1);
}

/*
** check_map_validity:
**  - Fills map dimensions (removing trailing newlines).
**  - Checks rectangle, walls, char counts.
**  - Then calls check_path() to ensure accessibility.
*/
int check_map_validity(t_map *map_data)
{
    if (!map_data->map_array)
        return (ft_printf("Error\nInvalid map array.\n"), 0);
    if (!fill_map_dimensions(map_data))
        return (0);
    if (!check_rectangle(map_data))
        return (0);
    if (!check_walls(map_data))
        return (0);
    if (!check_chars_count(map_data))
        return (0);
    if (!check_path(map_data))
        return (0);
    return (1);
}
