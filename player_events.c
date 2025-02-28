/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anebbou <anebbou@student42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 10:00:00 by anebbou           #+#    #+#             */
/*   Updated: 2025/02/28 13:06:58 by anebbou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	lose_game(t_game *game)
{
	game->map->player_lives--;
	if (game->map->player_lives <= 0)
	{
		ft_printf("Game Over! You lost all lives.\n");
		close_game(game);
		return ;
	}
	ft_printf("You got hit! Lives left: %d\n", game->map->player_lives);
	respawn_player(game);
}

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
