#include "so_long.h"
#include <stdlib.h> // For rand()

/*
** handle_keypress:
**  - WASD to move.
**  - ESC to close.
**  - After each move, monsters move too.
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

	// Move monsters after player's turn
	move_monsters(game);

	return (0);
}

/*
** move_monsters:
**  - Moves all monsters **only after the player moves**.
**  - Ensures they **don't delete collectibles** when passing over them.
*/
void move_monsters(t_game *game)
{
	int y, x, new_y, new_x, direction;
	char previous_tile;

	for (y = 0; y < game->map->height; y++)
	{
		for (x = 0; x < game->map->width; x++)
		{
			if (game->map->map_array[y][x] == 'M') // Found a monster
			{
				// Generate random movement: 0 = Up, 1 = Down, 2 = Left, 3 = Right
				direction = rand() % 4;
				new_y = y;
				new_x = x;

				if (direction == 0)
					new_y--; // Up
				else if (direction == 1)
					new_y++; // Down
				else if (direction == 2)
					new_x--; // Left
				else if (direction == 3)
					new_x++; // Right

				// Check if the new position is valid (monsters can walk over collectibles)
				if (new_y >= 0 && new_x >= 0 &&
					new_y < game->map->height && new_x < game->map->width &&
					(game->map->map_array[new_y][new_x] == '0' ||
					 game->map->map_array[new_y][new_x] == 'C' ||
					 game->map->map_array[new_y][new_x] == 'P'))
				{
					// Store the tile that was here before (to restore it later)
					previous_tile = game->map->map_array[new_y][new_x];

					// If monster moves into the player, player loses a life
					if (previous_tile == 'P')
					{
						lose_game(game);
					}

					// Move monster
					game->map->map_array[y][x] = (game->map->map_array[y][x] == 'C') ? 'C' : '0'; // Restore collectible if needed
					game->map->map_array[new_y][new_x] = 'M';

					// Restore previous tile (if collectible, keep it after move)
					if (previous_tile == 'C')
						game->map->map_array[y][x] = 'C';
				}
			}
		}
	}

	// Re-render after monsters move
	render_map(game);
}

/*
** lose_game:
**  - If player touches a monster, decrease lives.
**  - If lives reach 0, print "Game Over!" and close the game.
**  - Otherwise, display remaining lives.
*/
void lose_game(t_game *game)
{
	game->map->player_lives--;

	if (game->map->player_lives <= 0)
	{
		ft_printf("Game Over! You lost all your lives.\n");
		close_game(game);
	}
	else
	{
		ft_printf("You got hit! Lives left: %d\n", game->map->player_lives);
	}
}

/*
** move_player:
**  - If player moves onto 'M', they lose a life instead of instant death.
**  - If lives reach 0, the game ends.
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

	// If it's a wall, ignore movement
	if (game->map->map_array[new_x][new_y] == '1')
		return;

	// If next cell is a monster, lose a life
	if (game->map->map_array[new_x][new_y] == 'M')
	{
		lose_game(game);
		return;
	}

	// If next cell is an exit and all collectibles are collected, player wins
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

	// Move player
	game->map->map_array[game->map->player_x][game->map->player_y] = '0';
	game->map->map_array[new_x][new_y] = 'P';
	game->map->player_x = new_x;
	game->map->player_y = new_y;
	game->map->moves++;

	ft_printf("Moves: %d | Lives: %d\n", game->map->moves, game->map->player_lives);

	render_map(game);
}
