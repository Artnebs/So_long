/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anebbou <anebbou@student42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:56:44 by anebbou           #+#    #+#             */
/*   Updated: 2025/02/04 16:40:50 by anebbou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* Function prototypes */
static void put_tile(t_map *map_data, int i, int j);
static void put_player(t_map *map_data, int i, int j);

/*
** render_map:
**  - Iterates over map_array
**  - Chooses the right texture for each cell
**  - Places it in the window
*/
int render_map(t_map *map_data)
{
    int i;
    int j;

    i = 0;
    while (i < map_data->height)
    {
        j = 0;
        while (j < map_data->width)
        {
            put_tile(map_data, i, j);
            j++;
        }
        i++;
    }
    return (1);
}

/*
** put_tile:
**  - Takes row/column, checks map_data->map_array[i][j]
**  - Puts the appropriate texture.
*/
static void put_tile(t_map *map_data, int i, int j)
{
    if (map_data->map_array[i][j] == '1')
        mlx_put_image_to_window(map_data->mlx, map_data->win,
                                map_data->tex_wall, j * TILE_SIZE, i * TILE_SIZE);
    else if (map_data->map_array[i][j] == '0')
        mlx_put_image_to_window(map_data->mlx, map_data->win,
                                map_data->tex_floor, j * TILE_SIZE, i * TILE_SIZE);
    else if (map_data->map_array[i][j] == 'C')
        mlx_put_image_to_window(map_data->mlx, map_data->win,
                                map_data->tex_collect, j * TILE_SIZE, i * TILE_SIZE);
    else if (map_data->map_array[i][j] == 'E')
        mlx_put_image_to_window(map_data->mlx, map_data->win,
                                map_data->tex_exit, j * TILE_SIZE, i * TILE_SIZE);
    else if (map_data->map_array[i][j] == 'M')
        mlx_put_image_to_window(map_data->mlx, map_data->win,
                                map_data->tex_monster, j * TILE_SIZE, i * TILE_SIZE);
    else if (map_data->map_array[i][j] == 'P')
        put_player(map_data, i, j);
}

/*
** put_player:
**  - This is where you can handle animation frames for the player.
**  - For now, just place the primary player texture.
*/
static void put_player(t_map *map_data, int i, int j)
{
    mlx_put_image_to_window(map_data->mlx, map_data->win,
                            map_data->tex_player, j * TILE_SIZE, i * TILE_SIZE);
    map_data->player_x = i;
    map_data->player_y = j;
}
