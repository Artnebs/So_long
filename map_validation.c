/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anebbou <anebbou@student42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:28:27 by anebbou           #+#    #+#             */
/*   Updated: 2025/02/09 16:05:30 by anebbou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* Function prototype for fill_map_dimensions */
static int fill_map_dimensions(t_map *map_data)
{
	int i = 0;

	while (map_data->map_array && map_data->map_array[i])
	{
		// 🔥 Supprime le saut de ligne s'il est présent en fin de ligne
		int len = ft_strlen(map_data->map_array[i]);
		if (len > 0 && map_data->map_array[i][len - 1] == '\n')
			map_data->map_array[i][len - 1] = '\0';

		i++;
	}

	map_data->height = i;
	if (map_data->height == 0)
		return (ft_printf("Error\nEmpty map.\n"), 0);

	map_data->width = ft_strlen(map_data->map_array[0]); // 🔥 Maintenant bien calculé
	printf("Map width: %d, Map height: %d\n", map_data->width, map_data->height);
	return (1);
}

/*
** check_map_validity:
**  - Populates width, height in t_map.
**  - Runs multiple checks (rectangular, walls, required chars).
**  - Calls path check (DFS/BFS) to ensure all collectables & exit are reachable.
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


int check_rectangle(t_map *map_data)
{
    int i;
    int first_width;

    i = 0;
    first_width = map_data->width;
    while (map_data->map_array[i])
    {
        if ((int)ft_strlen(map_data->map_array[i]) != first_width)
            return (ft_printf("Error\nMap is not rectangular.\n"), 0);
        i++;
    }
    return (1);
}

int check_walls(t_map *map_data)
{
    int i;
    int last_row;

	i = 0;
    last_row = map_data->height - 1;
	
	printf("First line: %s\n", map_data->map_array[0]);
	printf("Last line: %s\n", map_data->map_array[last_row]);
	
	while (i < map_data->width)
    {
		printf("Checking: First row[%d] = '%c', Last row[%d] = '%c'\n",
			   i, map_data->map_array[0][i], i, map_data->map_array[last_row][i]);
			   
		if (map_data->map_array[0][i] != '1' || map_data->map_array[last_row][i] != '1')
            return (ft_printf("Error\nTop or bottom wall missing.\n"), 0);
        i++;
    }
    i = 0;
    while (i < map_data->height)
    {
        if (map_data->map_array[i][0] != '1' || map_data->map_array[i][map_data->width - 1] != '1')
            return (ft_printf("Error\nSide wall missing.\n"), 0);
        i++;
    }
    return (1);
}

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
                map_data->player_count++;
            else if (c == 'E')
                map_data->exit_count++;
            else if (c == 'C')
                map_data->collect_count++;
            else if (c != '0' && c != '1' && c != 'M')
                return (ft_printf("Error\nInvalid char in map.\n"), 0);
            j++;
        }
        i++;
    }
    if (map_data->player_count != 1 || map_data->exit_count == 0 || map_data->collect_count == 0)
        return (ft_printf("Error\nMissing P/E/C.\n"), 0);
    return (1);
}