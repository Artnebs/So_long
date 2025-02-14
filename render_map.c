#include "so_long.h"

/*
** draw_tile:
**  - Draws a fallback color tile using mlx_pixel_put if textures are missing.
*/
static void draw_tile(t_game *game, int y, int x, int color)
{
	int i;
	int j;

	if (!game->mlx->win)
		return;
	i = 0;
	while (i < TILE_SIZE)
	{
		j = 0;
		while (j < TILE_SIZE)
		{
			mlx_pixel_put(game->mlx->id,
						  game->mlx->win,
						  x * TILE_SIZE + j,
						  y * TILE_SIZE + i,
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
*/
void put_texture_tile(t_game *game, int y, int x, char c)
{
	if (c == '1')
		mlx_put_image_to_window(game->mlx->id, game->mlx->win,
								game->textures->wall, x * TILE_SIZE, y * TILE_SIZE);
	else if (c == 'P')
		mlx_put_image_to_window(game->mlx->id, game->mlx->win,
								game->textures->player, x * TILE_SIZE, y * TILE_SIZE);
	else if (c == 'C')
		mlx_put_image_to_window(game->mlx->id, game->mlx->win,
								game->textures->collectible, x * TILE_SIZE, y * TILE_SIZE);
	else if (c == 'E')
		mlx_put_image_to_window(game->mlx->id, game->mlx->win,
								game->textures->exit, x * TILE_SIZE, y * TILE_SIZE);
	else if (c == 'M')
		mlx_put_image_to_window(game->mlx->id, game->mlx->win,
								game->textures->monster, x * TILE_SIZE, y * TILE_SIZE);
	else
		mlx_put_image_to_window(game->mlx->id, game->mlx->win,
								game->textures->floor, x * TILE_SIZE, y * TILE_SIZE);
}

/*
** render_tile:
**  - Decides whether to draw a texture or a fallback color tile.
*/
void render_tile(t_game *game, int y, int x)
{
	char c;

	printf("DEBUG: Inside render_tile for tile (%d, %d)\n", y, x);

	if (!game || !game->map || !game->map->map_array)
	{
		printf("ERROR: Game or map is NULL!\n");
		return;
	}

	c = game->map->map_array[y][x];
	printf("DEBUG: Tile character is '%c'\n", c);

	if (!game->textures)
	{
		printf("ERROR: game->textures is NULL!\n");
		return;
	}

	/*
	** If ANY essential texture is missing, we fallback to color drawing
	*/
	if (!game->textures->wall || !game->textures->player ||
		!game->textures->collectible || !game->textures->exit ||
		!game->textures->floor || !game->textures->monster)
	{
		printf("DEBUG: Using fallback colors for tile (%d, %d)\n", y, x);
		if (c == '1')
			draw_tile(game, y, x, COLOR_WALL);
		else if (c == 'P')
			draw_tile(game, y, x, COLOR_PLAYER);
		else if (c == 'C')
			draw_tile(game, y, x, COLOR_COLLECT);
		else if (c == 'E')
			draw_tile(game, y, x, COLOR_EXIT);
		else if (c == 'M')
			draw_tile(game, y, x, COLOR_MONSTER);
		else
			draw_tile(game, y, x, COLOR_FLOOR);
	}
	else
	{
		printf("DEBUG: Using textures for tile (%d, %d)\n", y, x);
		put_texture_tile(game, y, x, c);
	}
	printf("DEBUG: Finished rendering tile (%d, %d)\n", y, x);
}

/*
** render_map:
**  - Clears window, then draws each cell of map_array.
**  - Logs debug info and prints the Collectibles/Lives count to the terminal.
*/
void render_map(t_game *game)
{
	int y;
	int x;
	char hud[64];

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
	ft_sprintf(hud, "Collectibles: %d | Lives: %d",
			   game->map->collect_count, game->map->player_lives);

	mlx_string_put(game->mlx->id, game->mlx->win, 10, 10, 0xFFFFFF, hud);
}
