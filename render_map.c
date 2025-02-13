#include "so_long.h"

/*
** draw_tile:
**  - Draws a colored tile at a given position using `mlx_pixel_put()`.
*/
void draw_tile(t_game *game, int y, int x, int color)
{
	int i;
	int j;

	if (!game->mlx->win)
	{
		ft_printf("DEBUG: draw_tile called but win is NULL!\n");
		return;
	}
	i = 0;
	while (i < TILE_SIZE)
	{
		j = 0;
		while (j < TILE_SIZE)
		{
			mlx_pixel_put(game->mlx->id, game->mlx->win, x * TILE_SIZE + j, y * TILE_SIZE + i, color);
			j++;
		}
		i++;
	}
}

/*
** render_map:
**  - Iterates over the map and draws each cell.
**  - Displays collectibles and lives in the UI.
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
			if (!game->textures->wall || !game->textures->player ||
				!game->textures->collectible || !game->textures->exit || !game->textures->floor)
			{
				if (game->map->map_array[y][x] == '1')
					draw_tile(game, y, x, COLOR_WALL);
				else if (game->map->map_array[y][x] == 'P')
					draw_tile(game, y, x, COLOR_PLAYER);
				else if (game->map->map_array[y][x] == 'C')
					draw_tile(game, y, x, COLOR_COLLECT);
				else if (game->map->map_array[y][x] == 'E')
					draw_tile(game, y, x, COLOR_EXIT);
				else if (game->map->map_array[y][x] == 'M')
					draw_tile(game, y, x, COLOR_MONSTER);
				else
					draw_tile(game, y, x, COLOR_FLOOR);
			}
			else
			{
				if (game->map->map_array[y][x] == '1')
					mlx_put_image_to_window(game->mlx->id, game->mlx->win, game->textures->wall, x * TILE_SIZE, y * TILE_SIZE);
				else if (game->map->map_array[y][x] == 'P')
					mlx_put_image_to_window(game->mlx->id, game->mlx->win, game->textures->player, x * TILE_SIZE, y * TILE_SIZE);
				else if (game->map->map_array[y][x] == 'C')
					mlx_put_image_to_window(game->mlx->id, game->mlx->win, game->textures->collectible, x * TILE_SIZE, y * TILE_SIZE);
				else if (game->map->map_array[y][x] == 'E')
					mlx_put_image_to_window(game->mlx->id, game->mlx->win, game->textures->exit, x * TILE_SIZE, y * TILE_SIZE);
				else if (game->map->map_array[y][x] == 'M')
					mlx_put_image_to_window(game->mlx->id, game->mlx->win, game->textures->monster, x * TILE_SIZE, y * TILE_SIZE);
				else if (game->textures->floor)
					mlx_put_image_to_window(game->mlx->id, game->mlx->win, game->textures->floor, x * TILE_SIZE, y * TILE_SIZE);
			}
			x++;
		}
		y++;
	}

	// Draw UI Elements (Collectibles & Lives)
	char status[100];
	snprintf(status, sizeof(status), "Collectibles: %d | Lives: %d", game->map->collect_count, game->map->player_lives);
	mlx_string_put(game->mlx->id, game->mlx->win, 10, 10, 0xFFFFFF, status);
}
