/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anebbou <anebbou@student42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 10:00:00 by anebbou           #+#    #+#             */
/*   Updated: 2025/02/28 13:04:22 by anebbou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	reset_player_position(t_map *map)
{
	while (map->map_array[map->player_x][map->player_y] == '1'
			|| map->map_array[map->player_x][map->player_y] == 'M')
	{
		map->player_x++;
		if (map->player_x >= map->height)
		{
			map->player_x = 0;
			map->player_y++;
			if (map->player_y >= map->width)
				map->player_y = 0;
		}
	}
}

void	respawn_player(t_game *game)
{
	game->map->player_lives--;
	if (game->map->player_lives <= 0)
	{
		ft_printf("Game Over! You lost all lives.\n");
		close_game(game);
		return ;
	}
	game->map->map_array[game->map->player_x][game->map->player_y] = '0';
	game->map->player_x = game->map->spawn_x;
	game->map->player_y = game->map->spawn_y;
	reset_player_position(game->map);
	game->map->map_array[game->map->player_x][game->map->player_y] = 'P';
	render_map(game);
}

static void	handle_move_result(t_game *game, int new_x, int new_y)
{
	if (game->map->map_array[new_x][new_y] == 'C')
	{
		game->map->collect_count--;
		game->map->map_array[new_x][new_y] = '0';
	}
	game->map->map_array[game->map->player_x][game->map->player_y] = '0';
	game->map->map_array[new_x][new_y] = 'P';
	game->map->player_x = new_x;
	game->map->player_y = new_y;
	game->map->moves++;
	ft_printf("Moves: %d | Lives: %d\n",
		game->map->moves, game->map->player_lives);
	render_map(game);
}

void	move_player(t_game *game, int dx, int dy)
{
	int	nx;
	int	ny;

	nx = game->map->player_x + dx;
	ny = game->map->player_y + dy;
	if (nx < 0 || ny < 0 || nx >= game->map->height || ny >= game->map->width)
		return ;
	if (game->map->map_array[nx][ny] == '1')
		return ;
	if (game->map->map_array[nx][ny] == 'M')
		return (respawn_player(game));
	if (game->map->map_array[nx][ny] == 'E' && game->map->collect_count == 0)
		return (win_game(game));
	if (game->map->map_array[nx][ny] == 'E')
		return ;
	handle_move_result(game, nx, ny);
}
