/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anebbou <anebbou@student42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:58:09 by anebbou           #+#    #+#             */
/*   Updated: 2025/02/04 15:58:16 by anebbou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
** close_game:
**  - Destroys images
**  - Destroys window
**  - Frees map
**  - Exits program
*/
int close_game(t_map *map_data)
{
	if (map_data->tex_wall)
		mlx_destroy_image(map_data->mlx, map_data->tex_wall);
	if (map_data->tex_floor)
		mlx_destroy_image(map_data->mlx, map_data->tex_floor);
	if (map_data->tex_player)
		mlx_destroy_image(map_data->mlx, map_data->tex_player);
	/* etc. for each texture... */

	if (map_data->win)
		mlx_destroy_window(map_data->mlx, map_data->win);

	free_map(map_data->map_array);
	exit(0);
	return (0);
}
