/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anebbou <anebbou@student42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:53:30 by anebbou           #+#    #+#             */
/*   Updated: 2025/02/04 15:53:35 by anebbou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
** init_window:
**  - Initializes MLX.
**  - Creates the window.
**  - Calls load_textures.
**  - Returns 1 on success, 0 on failure.
*/
int init_window(t_map *map_data)
{
	map_data->mlx = mlx_init();
	if (!map_data->mlx)
	{
		ft_printf("Error\nMLX init failed.\n");
		return (0);
	}
	map_data->win = mlx_new_window(map_data->mlx,
								   map_data->width * TILE_SIZE,
								   map_data->height * TILE_SIZE,
								   "So Long");
	if (!map_data->win)
	{
		ft_printf("Error\nWindow creation failed.\n");
		return (0);
	}
	if (!load_textures(map_data))
		return (0);
	return (1);
}
