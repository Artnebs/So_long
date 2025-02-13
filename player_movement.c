#include "so_long.h"

/*
** handle_keypress:
**  - WASD to move.
**  - ESC to close.
*/
int handle_keypress(int keycode, t_game *game)
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
	return (0);
}

/*
** move_player:
**  - dx, dy = direction of movement in row/col.
**  - Check walls. If next cell is a wall '1', don't move.
**  - If next cell is 'C', decrement collect_count and change to '0'.
**  - If next cell is 'E' and collect_count == 0 => win_game().
**  - Otherwise just move and update 'P' position in the map array.
**  - Then re-render the map.
*/
void move_player(t_game *game, int dx, int dy)
{
	int new_x;
	int new_y;

	new_x = game->map->player_x + dx;
	new_y = game->map->player_y + dy;

	// Check boundaries
	if (new_x < 0 || new_y < 0 || new_x >= game->map->height || new_y >= game->map->width)
		return;

	// If it's a wall, ignore
	if (game->map->map_array[new_x][new_y] == '1')
		return;

	// If next cell is exit and we have no more collectibles, we win
	if (game->map->map_array[new_x][new_y] == 'E')
	{
		if (game->map->collect_count == 0)
			win_game(game);
		return;
	}

	// If next cell is a collectible, pick it up
	if (game->map->map_array[new_x][new_y] == 'C')
	{
		game->map->collect_count--;
		game->map->map_array[new_x][new_y] = '0';
	}

	// Move: set old position to '0', new position to 'P'
	game->map->map_array[game->map->player_x][game->map->player_y] = '0';
	game->map->map_array[new_x][new_y] = 'P';
	game->map->player_x = new_x;
	game->map->player_y = new_y;

	// Increment moves count
	game->map->moves++;
	ft_printf("Moves: %d\n", game->map->moves);

	// Re-render after movement
	render_map(game);
}
