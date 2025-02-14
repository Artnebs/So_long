#include "so_long.h"

/*
** init_window:
**  - Uses mlx_get_screen_size to get max screen size (if available).
**  - Creates window, then calls render_map once.
*/
int init_window(t_game *game)
{
	int screen_width;
	int screen_height;

	ft_printf("DEBUG: Getting screen size\n");
	mlx_get_screen_size(game->mlx->id, &screen_width, &screen_height);

	ft_printf("DEBUG: screen_width=%d screen_height=%d\n", screen_width, screen_height);

	game->mlx->win_width = game->map->width * TILE_SIZE;
	game->mlx->win_height = game->map->height * TILE_SIZE;
	if (game->mlx->win_width > screen_width)
		game->mlx->win_width = screen_width;
	if (game->mlx->win_height > screen_height)
		game->mlx->win_height = screen_height;

	ft_printf("DEBUG: Creating window\n");
	game->mlx->win = mlx_new_window(game->mlx->id,
									game->mlx->win_width,
									game->mlx->win_height,
									"so_long");
	if (!game->mlx->win)
		return (ft_printf("Error\nFailed to create window.\n"), 1);

	ft_printf("DEBUG: Clearing window\n");
	mlx_clear_window(game->mlx->id, game->mlx->win);

	ft_printf("DEBUG: Rendering map\n");
	render_map(game);

	ft_printf("DEBUG: Window created %dx%d (Screen: %dx%d)\n",
			  game->mlx->win_width, game->mlx->win_height,
			  screen_width, screen_height);

	return (0);
}
