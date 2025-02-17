/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize_hook.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anebbou <anebbou@student42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 10:00:00 by anebbou           #+#    #+#             */
/*   Updated: 2025/02/15 15:14:30 by anebbou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int resize_hook(int width, int height, t_game *game)
{
	if (width < 100 || height < 100)
		return (0);
	if (!game || !game->mlx || !game->mlx->win)
		return (0);
	mlx_destroy_window(game->mlx->id, game->mlx->win);
	game->mlx->win_width = width;
	game->mlx->win_height = height;
	game->mlx->win = mlx_new_window(game->mlx->id, width, height, "so_long");
	if (!game->mlx->win)
		return (0);
	mlx_clear_window(game->mlx->id, game->mlx->win);
	render_map(game);
	return (0);
}
