#include "so_long.h"

int resize_hook(int width, int height, t_game *game)
{
	if (width < 100 || height < 100)
		return (ft_printf("Error\nToo small window.\n"), 0);
	if (!game || !game->mlx || !game->mlx->win)
		return (ft_printf("Error\nGame or window is NULL.\n"), 0);
	mlx_destroy_window(game->mlx->id, game->mlx->win);
	game->mlx->win_width = width;
	game->mlx->win_height = height;
	game->mlx->win = mlx_new_window(game->mlx->id, width, height, "so_long");
	if (!game->mlx->win)
		return (ft_printf("Error\nFailed to recreate window.\n"), 0);
	mlx_clear_window(game->mlx->id, game->mlx->win);
	render_map(game);
	return (0);
}
