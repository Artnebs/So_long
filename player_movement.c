/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anebbou <anebbou@student42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:57:31 by anebbou           #+#    #+#             */
/*   Updated: 2025/02/04 15:57:36 by anebbou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* Adjust keycodes for your system or define them in your so_long.h */
#define KEY_W 119
#define KEY_S 115
#define KEY_A 97
#define KEY_D 100
#define KEY_ESC 65307

int handle_keypress(int keycode, t_map *map_data)
{
	if (keycode == KEY_ESC)
		close_game(map_data);
	else if (keycode == KEY_W)
		move_player(map_data, -1, 0);
	else if (keycode == KEY_S)
		move_player(map_data, 1, 0);
	else if (keycode == KEY_A)
		move_player(map_data, 0, -1);
	else if (keycode == KEY_D)
		move_player(map_data, 0, 1);
	return (0);
}

/*
** move_player:
**  - Checks if next cell is wall => ignore
**  - If collectible => increment collected, set cell to '0'
**  - If exit => check if all collects are done => win => close_game
**  - Otherwise, update map with new player position
*/
void move_player(t_map *map_data, int dx, int dy)
{
	int new_x;
	int new_y;
	char next_cell;

	new_x = map_data->player_x + dx;
	new_y = map_data->player_y + dy;
	next_cell = map_data->map_array[new_x][new_y];
	if (next_cell == '1')
		return; /* blocked by wall */

	if (next_cell == 'C')
	{
		map_data->collect_count--;
		map_data->map_array[new_x][new_y] = '0';
	}
	else if (next_cell == 'E')
	{
		if (map_data->collect_count == 0)
		{
			ft_printf("You collected all items! You win!\n");
			close_game(map_data);
		}
		return;
	}

	/* Update map: remove old 'P', place new 'P' */
	map_data->map_array[map_data->player_x][map_data->player_y] = '0';
	map_data->map_array[new_x][new_y] = 'P';
	map_data->player_x = new_x;
	map_data->player_y = new_y;

	map_data->moves++;
	ft_printf("Moves: %d\n", map_data->moves);

	/* Re-render the map to show changes */
	render_map(map_data);
}
