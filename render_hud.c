/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_hud.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anebbou <anebbou@student42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 10:00:00 by anebbou           #+#    #+#             */
/*   Updated: 2025/02/28 13:21:00 by anebbou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	draw_hud_line(t_game *game, int y)
{
	int	j;

	j = 0;
	while (j < game->mlx->win_width)
	{
		mlx_pixel_put(game->mlx->id, game->mlx->win, j, y, 0x000000);
		j++;
	}
}

static void	draw_hud_background(t_game *game)
{
	int	i;

	i = 0;
	while (i < HUD_HEIGHT)
	{
		draw_hud_line(game, i);
		i++;
	}
}

static void	draw_hud_textures(t_game *game)
{
	if (game->textures->hud_moves)
		mlx_put_image_to_window(game->mlx->id, game->mlx->win,
			game->textures->hud_moves, 10, 10);
	if (game->textures->hud_collect)
		mlx_put_image_to_window(game->mlx->id, game->mlx->win,
			game->textures->hud_collect, 120, 10);
	if (game->textures->hud_lives)
		mlx_put_image_to_window(game->mlx->id, game->mlx->win,
			game->textures->hud_lives, 230, 10);
}

static void	draw_hud_text(t_game *game, char *moves,
				char *collectibles, char *lives)
{
	mlx_string_put(game->mlx->id, game->mlx->win, 50, 20, 0xFFFFFF, moves);
	mlx_string_put(game->mlx->id, game->mlx->win, 160, 20, 0xFFFFFF,
		collectibles);
	mlx_string_put(game->mlx->id, game->mlx->win, 270, 20, 0xFFFFFF, lives);
}

void	render_hud(t_game *game)
{
	char	moves[10];
	char	collectibles[10];
	char	lives[10];

	if (!game || !game->map || !game->mlx || !game->textures)
		return ;
	ft_sprintf(moves, "%d", game->map->moves);
	ft_sprintf(collectibles, "%d", game->map->collect_count);
	ft_sprintf(lives, "%d", game->map->player_lives);
	draw_hud_background(game);
	draw_hud_textures(game);
	draw_hud_text(game, moves, collectibles, lives);
}
