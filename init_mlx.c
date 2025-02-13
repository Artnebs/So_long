#include "so_long.h"

/*
** init_mlx:
** - Allocates the t_mlx struct inside game->mlx.
** - Initializes MLX (game->mlx->id).
** - Does NOT create a window yet (that is done by init_window()).
** Return 0 on success, 1 on error.
*/
int init_mlx(t_game *game)
{
	game->mlx = (t_mlx *)ft_calloc(1, sizeof(t_mlx));
	if (!game->mlx)
	{
		ft_printf("Error\nFailed to allocate t_mlx.\n");
		return (1);
	}
	game->mlx->id = mlx_init();
	if (!game->mlx->id)
	{
		ft_printf("Error\nmlx_init() failed.\n");
		return (1);
	}
	return (0);
}

#include "so_long.h"

/*
** init_window:
** - Uses `mlx_get_screen_size` to get the max screen size.
** - Ensures the game fills the screen but maintains the aspect ratio.
*/
int init_window(t_game *game)
{
	int screen_width;
	int screen_height;

	// Get the max screen resolution
	mlx_get_screen_size(game->mlx->id, &screen_width, &screen_height);

	// Set window size based on map size (scaling)
	game->mlx->win_width = game->map->width * TILE_SIZE;
	game->mlx->win_height = game->map->height * TILE_SIZE;

	// Prevent exceeding screen limits
	if (game->mlx->win_width > screen_width)
		game->mlx->win_width = screen_width;
	if (game->mlx->win_height > screen_height)
		game->mlx->win_height = screen_height;

	// Create the window
	game->mlx->win = mlx_new_window(game->mlx->id, game->mlx->win_width, game->mlx->win_height, "so_long");
	if (!game->mlx->win)
		return (ft_printf("Error\nFailed to create window.\n"), 1);

	// Force a full re-render
	mlx_clear_window(game->mlx->id, game->mlx->win);
	render_map(game);

	ft_printf("DEBUG: Window created with size %dx%d (Screen: %dx%d)\n",
			  game->mlx->win_width, game->mlx->win_height, screen_width, screen_height);

	return (0);
}
