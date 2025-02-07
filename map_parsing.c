/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anebbou <anebbou@student42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 12:41:28 by anebbou           #+#    #+#             */
/*   Updated: 2025/02/04 16:37:20 by anebbou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* Function prototype for copy_old_map */
static void copy_old_map(char **old_map, char **new_map, int count);

/*
** read_map_file:
**  - Opens the file.
**  - Reads each line with get_next_line.
**  - Stores them in a newly allocated char**.
*/
char **read_map_file(char *filename)
{
    int fd;
    char *line;
    char **map;
    char **temp;
    int count;

    fd = open(filename, O_RDONLY);
    if (fd < 0)
    {
        ft_printf("Error\nFailed to open file.\n");
        return (NULL);
    }
    map = NULL;
    count = 0;
    line = get_next_line(fd);
    while (line)
    {
        temp = map;
        map = malloc(sizeof(char *) * (count + 2));
        if (!map)
            return (free_map(temp), close(fd), ft_printf("Error\nMalloc.\n"), NULL);
        copy_old_map(temp, map, count); /* see helper below */
        map[count] = line;
        map[count + 1] = NULL;
        count++;
        line = get_next_line(fd);
        free(temp);
    }
    close(fd);
    return (map);
}

/*
** copy_old_map:
**  - Copies previous pointers from old `map` to new `map`.
**  - Then frees the old pointer array (not the lines themselves).
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
** free_map:
**  - Frees each line in the array, then frees the array itself.
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