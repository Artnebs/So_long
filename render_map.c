#include "so_long.h"

/*
** draw_tile:
**  - Draw a single TILE_SIZE x TILE_SIZE square using mlx_pixel_put().
**    We added a safety check and a debug print to help diagnose crashes.
*/
void draw_tile(t_game *game, int y, int x, int color)
{
	int i;
	int j;

	/* Safety check: make sure the window pointer is valid */
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
			mlx_pixel_put(
				game->mlx->id,
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
** render_map:
**  - Iterates over map_array and draws each cell.
**  - If textures are loaded (non-null), you use mlx_put_image_to_window().
**    Otherwise fallback to color placeholders using draw_tile().
**
** We've added a debug print in the fallback branch so you see exactly which tile
** is being drawn with colors.
*/
void render_map(t_game *game)
{
	int y;
	int x;

	y = 0;
	while (y < game->map->height)
	{
		x = 0;
		while (x < game->map->width)
		{
			/*
			** Force using colors when textures are missing:
			** If ANY texture pointer is missing, we go color fallback.
			*/
			if (!game->textures || !game->textures->wall ||
				!game->textures->player || !game->textures->collectible ||
				!game->textures->exit || !game->textures->floor)
			{
				ft_printf("DEBUG: fallback tile at y=%d x=%d -> %c\n",
						  y, x, game->map->map_array[y][x]);

				if (game->map->map_array[y][x] == '1') // Wall
					draw_tile(game, y, x, COLOR_WALL);
				else if (game->map->map_array[y][x] == 'P') // Player
					draw_tile(game, y, x, COLOR_PLAYER);
				else if (game->map->map_array[y][x] == 'C') // Collectible
					draw_tile(game, y, x, COLOR_COLLECT);
				else if (game->map->map_array[y][x] == 'E') // Exit
					draw_tile(game, y, x, COLOR_EXIT);
				else // Floor
					draw_tile(game, y, x, COLOR_FLOOR);
			}
			else
			{
				// **Otherwise, use textures**
				if (game->map->map_array[y][x] == '1' && game->textures->wall)
					mlx_put_image_to_window(game->mlx->id, game->mlx->win, game->textures->wall, x * TILE_SIZE, y * TILE_SIZE);
				else if (game->map->map_array[y][x] == 'P' && game->textures->player)
					mlx_put_image_to_window(game->mlx->id, game->mlx->win, game->textures->player, x * TILE_SIZE, y * TILE_SIZE);
				else if (game->map->map_array[y][x] == 'C' && game->textures->collectible)
					mlx_put_image_to_window(game->mlx->id, game->mlx->win, game->textures->collectible, x * TILE_SIZE, y * TILE_SIZE);
				else if (game->map->map_array[y][x] == 'E' && game->textures->exit)
					mlx_put_image_to_window(game->mlx->id, game->mlx->win, game->textures->exit, x * TILE_SIZE, y * TILE_SIZE);
				else if (game->textures->floor) // Default case: floor
					mlx_put_image_to_window(game->mlx->id, game->mlx->win, game->textures->floor, x * TILE_SIZE, y * TILE_SIZE);
			}
			x++;
		}
		y++;
	}
}
