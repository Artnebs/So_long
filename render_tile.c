/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_tile.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anebbou <anebbou@student42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 10:00:00 by anebbou           #+#    #+#             */
/*   Updated: 2025/02/28 13:24:37 by anebbou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	draw_tile(t_game *game, int y, int x, int color)
{
	int	i;
	int	j;

	if (!game->mlx->win)
		return ;
	i = 0;
	while (i < TILE_SIZE)
	{
		j = 0;
		while (j < TILE_SIZE)
		{
			mlx_pixel_put(game->mlx->id, game->mlx->win,
				x * TILE_SIZE + j, (y * TILE_SIZE + i) + HUD_HEIGHT, color);
			j++;
		}
		i++;
	}
}

static void	put_texture_tile_helper(t_game *game, int y, int x, char c)
{
	if (c == '1')
		mlx_put_image_to_window(game->mlx->id, game->mlx->win,
			game->textures->wall, x * TILE_SIZE, (y * TILE_SIZE) + HUD_HEIGHT);
	else if (c == 'P')
		mlx_put_image_to_window(game->mlx->id, game->mlx->win,
			game->textures->player, x * TILE_SIZE,
			(y * TILE_SIZE) + HUD_HEIGHT);
	else if (c == 'C')
		mlx_put_image_to_window(game->mlx->id, game->mlx->win,
			game->textures->collectible, x * TILE_SIZE,
			(y * TILE_SIZE) + HUD_HEIGHT);
	else if (c == 'E')
		mlx_put_image_to_window(game->mlx->id, game->mlx->win,
			game->textures->exit, x * TILE_SIZE, (y * TILE_SIZE) + HUD_HEIGHT);
	else if (c == 'M')
		mlx_put_image_to_window(game->mlx->id, game->mlx->win,
			game->textures->monster, x * TILE_SIZE,
			(y * TILE_SIZE) + HUD_HEIGHT);
	else
		mlx_put_image_to_window(game->mlx->id, game->mlx->win,
			game->textures->floor, x * TILE_SIZE, (y * TILE_SIZE) + HUD_HEIGHT);
}

void	put_texture_tile(t_game *game, int y, int x, char c)
{
	if (c == 'm')
		c = 'M';
	put_texture_tile_helper(game, y, x, c);
}

static void	draw_tile_helper(t_game *game, int y, int x, char c)
{
	if (c == '1')
		draw_tile(game, y, x, COLOR_WALL);
	else if (c == 'P')
		draw_tile(game, y, x, COLOR_PLAYER);
	else if (c == 'C')
		draw_tile(game, y, x, COLOR_COLLECT);
	else if (c == 'E')
		draw_tile(game, y, x, COLOR_EXIT);
	else if (c == 'm' || c == 'M')
		draw_tile(game, y, x, COLOR_MONSTER);
	else
		draw_tile(game, y, x, COLOR_FLOOR);
}

void	render_tile(t_game *game, int y, int x)
{
	char	c;

	if (!game || !game->map || !game->map->map_array)
		return ;
	c = game->map->map_array[y][x];
	if (!game->textures)
		return ;
	if (!game->textures->wall || !game->textures->player
		|| !game->textures->collectible || !game->textures->exit
		|| !game->textures->floor || !game->textures->monster)
		draw_tile_helper(game, y, x, c);
	else
		put_texture_tile(game, y, x, c);
}
