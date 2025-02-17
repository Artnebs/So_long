/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anebbou <anebbou@student42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 10:00:00 by anebbou           #+#    #+#             */
/*   Updated: 2025/02/15 15:19:08 by anebbou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_textures(t_game *game)
{
	if (!game->textures)
		return ;
	if (game->textures->wall)
		mlx_destroy_image(game->mlx->id, game->textures->wall);
	if (game->textures->floor)
		mlx_destroy_image(game->mlx->id, game->textures->floor);
	if (game->textures->player)
		mlx_destroy_image(game->mlx->id, game->textures->player);
	if (game->textures->collectible)
		mlx_destroy_image(game->mlx->id, game->textures->collectible);
	if (game->textures->exit)
		mlx_destroy_image(game->mlx->id, game->textures->exit);
	if (game->textures->monster)
		mlx_destroy_image(game->mlx->id, game->textures->monster);
	if (game->textures->hud_moves)
		mlx_destroy_image(game->mlx->id, game->textures->hud_moves);
	if (game->textures->hud_collect)
		mlx_destroy_image(game->mlx->id, game->textures->hud_collect);
	if (game->textures->hud_lives)
		mlx_destroy_image(game->mlx->id, game->textures->hud_lives);
	free(game->textures);
	game->textures = NULL;
}

int	close_game(t_game *game)
{
	if (!game)
		exit(0);
	stop_background_music();
	if (game->mlx && game->mlx->win)
		mlx_destroy_window(game->mlx->id, game->mlx->win);
	free_textures(game);
	if (game->map)
	{
		free_map(game->map->map_array);
		free(game->map);
		game->map = NULL;
	}
	if (game->mlx)
	{
		free(game->mlx);
		game->mlx = NULL;
	}
	free(game);
	exit(0);
	return (0);
}

void	win_game(t_game *game)
{
	ft_printf("You win!\n");
	close_game(game);
}
