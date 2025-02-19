/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anebbou <anebbou@student42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 10:00:00 by anebbou           #+#    #+#             */
/*   Updated: 2025/02/19 17:43:26 by anebbou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* If player is killed or steps on 'M', lose a life or end the game */
void	respawn_player(t_game *game)
{
	game->map->player_lives--;
	if (game->map->player_lives <= 0)
	{
		ft_printf("Game Over! You lost all lives.\n");
		close_game(game);
	}
	else
	{
		game->map->map_array[game->map->player_x][game->map->player_y] = '0';
		game->map->player_x = game->map->spawn_x;
		game->map->player_y = game->map->spawn_y;
		while (game->map->map_array[game->map->player_x][game->map->player_y] == '1'
			|| game->map->map_array[game->map->player_x][game->map->player_y] == 'M')
		{
			game->map->player_x++;
			if (game->map->player_x >= game->map->height)
			{
				game->map->player_x = 0;
				game->map->player_y++;
				if (game->map->player_y >= game->map->width)
					game->map->player_y = 0;
			}
		}
		game->map->map_array[game->map->player_x][game->map->player_y] = 'P';
		render_map(game);
	}
}

/* Helper after a valid move to a new tile */
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
	ft_printf("Moves: %d | Lives: %d\n", game->map->moves, game->map->player_lives);
	render_map(game);
}

/* Called by keypress to move the player in direction (dx, dy) */
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
	{
		respawn_player(game);
		return ;
	}
	if (game->map->map_array[nx][ny] == 'E')
	{
		if (game->map->collect_count == 0)
			win_game(game);
		return ;
	}
	handle_move_result(game, nx, ny);
}

/* If a monster steps on the player, we lose a life or end the game */
void	lose_game(t_game *game)
{
	game->map->player_lives--;
	if (game->map->player_lives <= 0)
	{
		ft_printf("Game Over! You lost all lives.\n");
		close_game(game);
	}
	else
	{
		ft_printf("You got hit! Lives left: %d\n", game->map->player_lives);
		respawn_player(game);
	}
}

/* The main key handler */
int	handle_keypress(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		close_game(game);
	else if (keycode == KEY_W)
		move_player(game, -1, 0);
	else if (keycode == KEY_S)
		move_player(game, 1, 0);
	else if (keycode == KEY_A)
		move_player(game, 0, -1);
	else if (keycode == KEY_D)
		move_player(game, 0, 1);
	else if (keycode == KEY_M)
		toggle_music(game);
	move_monsters(game);
	return (0);
}
