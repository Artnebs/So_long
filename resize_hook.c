#include "so_long.h"

int resize_hook(int width, int height, t_game *game)
{
	ft_printf("DEBUG: Entering resize_hook. New size: %dx%d\n", width, height);

	// Validate dimensions
	if (width < 100 || height < 100 || width > 1920 || height > 1080)
		return (ft_printf("ERROR: Invalid width/height received (%d, %d)\n", width, height), 0);

	if (!game || !game->mlx || !game->mlx->win)
		return (ft_printf("ERROR: `game`, `game->mlx`, or `game->mlx->win` is NULL\n"), 0);

	// Destroy the old window
	mlx_destroy_window(game->mlx->id, game->mlx->win);

	// Set new dimensions
	game->mlx->win_width = width;
	game->mlx->win_height = height;

	// Recreate window
	game->mlx->win = mlx_new_window(game->mlx->id, game->mlx->win_width, game->mlx->win_height, "so_long");
	if (!game->mlx->win)
		return (ft_printf("ERROR: Failed to recreate window.\n"), 0);

	// Re-render the game
	mlx_clear_window(game->mlx->id, game->mlx->win);
	render_map(game);

	ft_printf("DEBUG: Window resized successfully.\n");
	return (0);
}
