/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anebbou <anebbou@student42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:54:53 by anebbou           #+#    #+#             */
/*   Updated: 2025/02/04 15:54:57 by anebbou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
** load_textures:
**  - Loads each tile's image (wall, floor, player, etc.).
**  - Returns 1 on success, 0 on failure.
*/
int load_textures(t_map *map_data)
{
	int w;
	int h;

	map_data->tex_wall = mlx_xpm_file_to_image(map_data->mlx, "textures/wall.xpm", &w, &h);
	if (!map_data->tex_wall)
		return (ft_printf("Error\nFailed to load wall.xpm\n"), 0);
	map_data->tex_floor = mlx_xpm_file_to_image(map_data->mlx, "textures/floor.xpm", &w, &h);
	if (!map_data->tex_floor)
		return (ft_printf("Error\nFailed to load floor.xpm\n"), 0);
	/* Repeat for player, exit, collectible, monster... */
	map_data->tex_player = mlx_xpm_file_to_image(map_data->mlx, "textures/player.xpm", &w, &h);
	if (!map_data->tex_player)
		return (ft_printf("Error\nFailed to load player.xpm\n"), 0);
	map_data->tex_exit = mlx_xpm_file_to_image(map_data->mlx, "textures/exit.xpm", &w, &h);
	/* etc. */

	return (1);
}

