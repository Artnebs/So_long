/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anebbou <anebbou@student42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 10:00:00 by anebbou           #+#    #+#             */
/*   Updated: 2025/02/15 15:12:41 by anebbou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
** draw_tile:
**  - Draws a fallback color tile using mlx_pixel_put if textures are missing.
**  - Now shifted down by HUD_HEIGHT so it doesn't overlap the HUD.
*/
static void	draw_tile(t_game *game, int y, int x, int color)
{
	int	i;
	int	j;

	if (!game->mlx->win)
		return;

	i = 0;
	while (i < TILE_SIZE)
	{
		j = 0;
		while (j < TILE_SIZE)
		{
			mlx_pixel_put(
				game->mlx->id,
				game->mlx->win,
				x * TILE_SIZE + j,
				(y * TILE_SIZE + i) + HUD_HEIGHT,
				color);
			j++;
		}
		i++;
	}
}

/*
** put_texture_tile:
**  - Places the correct texture image into the window at (x,y).
**  - Called if the textures are loaded (no fallback).
**  - Also shifted by HUD_HEIGHT in the Y direction.
*/
void put_texture_tile(t_game *game, int y, int x, char c)
{
	if (c == 'm')
		c = 'M';

	if (c == '1')
		mlx_put_image_to_window(
			game->mlx->id, game->mlx->win,
			game->textures->wall,
			x * TILE_SIZE,
			(y * TILE_SIZE) + HUD_HEIGHT);
	else if (c == 'P')
		mlx_put_image_to_window(
			game->mlx->id, game->mlx->win,
			game->textures->player,
			x * TILE_SIZE,
			(y * TILE_SIZE) + HUD_HEIGHT);
	else if (c == 'C')
		mlx_put_image_to_window(
			game->mlx->id, game->mlx->win,
			game->textures->collectible,
			x * TILE_SIZE,
			(y * TILE_SIZE) + HUD_HEIGHT);
	else if (c == 'E')
		mlx_put_image_to_window(
			game->mlx->id, game->mlx->win,
			game->textures->exit,
			x * TILE_SIZE,
			(y * TILE_SIZE) + HUD_HEIGHT);
	else if (c == 'M')
		mlx_put_image_to_window(
			game->mlx->id, game->mlx->win,
			game->textures->monster,
			x * TILE_SIZE,
			(y * TILE_SIZE) + HUD_HEIGHT);
	else
		mlx_put_image_to_window(
			game->mlx->id, game->mlx->win,
			game->textures->floor,
			x * TILE_SIZE,
			(y * TILE_SIZE) + HUD_HEIGHT);
}

/*
** render_tile:
**  - Decides whether to draw a texture or a fallback color tile.
**  - We pass the same (x,y) to either put_texture_tile or draw_tile,
**    which themselves handle the vertical offset.
*/
void render_tile(t_game *game, int y, int x)
{
	char c;

	if (!game || !game->map || !game->map->map_array)
		return;

	c = game->map->map_array[y][x];

	if (!game->textures)
		return;

	// If ANY essential texture is missing, fallback to color drawing
	if (!game->textures->wall || !game->textures->player ||
		!game->textures->collectible || !game->textures->exit ||
		!game->textures->floor || !game->textures->monster)
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
	else
	{
		put_texture_tile(game, y, x, c);
	}
}

/*
** render_hud:
**  - Renders the HUD with moves, collectibles, and lives at the top (0..HUD_HEIGHT-1).
*/
void render_hud(t_game *game)
{
	char moves[10];
	char collectibles[10];
	char lives[10];
	int i;
	int j;

	if (!game || !game->map || !game->mlx || !game->textures)
		return;

	ft_sprintf(moves, "%d", game->map->moves);
	ft_sprintf(collectibles, "%d", game->map->collect_count);
	ft_sprintf(lives, "%d", game->map->player_lives);

	// Draw HUD background (makes text easier to read)
	i = 0;
	while (i < HUD_HEIGHT)
	{
		j = 0;
		while (j < game->mlx->win_width)
		{
			mlx_pixel_put(game->mlx->id, game->mlx->win, j, i, 0x000000);
			j++;
		}
		i++;
	}

	if (game->textures->hud_moves)
		mlx_put_image_to_window(game->mlx->id, game->mlx->win,
								game->textures->hud_moves, 10, 10);
	if (game->textures->hud_collect)
		mlx_put_image_to_window(game->mlx->id, game->mlx->win,
								game->textures->hud_collect, 120, 10);
	if (game->textures->hud_lives)
		mlx_put_image_to_window(game->mlx->id, game->mlx->win,
								game->textures->hud_lives, 230, 10);

	mlx_string_put(game->mlx->id, game->mlx->win, 50, 20, 0xFFFFFF, moves);
	mlx_string_put(game->mlx->id, game->mlx->win, 160, 20, 0xFFFFFF, collectibles);
	mlx_string_put(game->mlx->id, game->mlx->win, 270, 20, 0xFFFFFF, lives);
}

/*
** render_map:
**  - Clears the window, draws each cell of map_array (shifted below the HUD),
**    and then overlays the HUD at the top.
*/
void render_map(t_game *game)
{
	int y;
	int x;

	mlx_clear_window(game->mlx->id, game->mlx->win);

	y = 0;
	while (y < game->map->height)
	{
		x = 0;
		while (x < game->map->width)
		{
			render_tile(game, y, x);
			x++;
		}
		y++;
	}

	render_hud(game);
}
