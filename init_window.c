/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anebbou <anebbou@student42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 10:00:00 by anebbou           #+#    #+#             */
/*   Updated: 2025/02/15 15:21:23 by anebbou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	init_window(t_game *game)
{
	int	screen_width;
	int	screen_height;

	mlx_get_screen_size(game->mlx->id, &screen_width, &screen_height);
	game->mlx->win_width = game->map->width * TILE_SIZE;
	game->mlx->win_height = game->map->height * TILE_SIZE + HUD_HEIGHT;
	if (game->mlx->win_width > screen_width)
		game->mlx->win_width = screen_width;
	if (game->mlx->win_height > screen_height)
		game->mlx->win_height = screen_height;
	game->mlx->win = mlx_new_window(
			game->mlx->id,
			game->mlx->win_width,
			game->mlx->win_height,
			"so_long");
	if (!game->mlx->win)
	{
		ft_printf("Error\nFailed to create window.\n");
		return (1);
	}
	mlx_clear_window(game->mlx->id, game->mlx->win);
	render_map(game);
	return (0);
}
