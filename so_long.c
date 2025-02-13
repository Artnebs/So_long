#include "so_long.h"

static int init_all(t_game *game, int argc, char **argv)
{
	if (init_mlx(game))
		return (1);

	// Ensure `game->map` is properly allocated
	game->map = ft_calloc(1, sizeof(t_map));
	if (!game->map)
		return (ft_printf("Error\nFailed to allocate t_map.\n"), 1);

	// Load map (either from file or default)
	if (argc == 2)
	{
		if (!parse_map(game, argv[1]))
			return (1);
	}
	else
	{
		ft_printf("No map provided, using default map.\n");
		load_default_map(game);
	}

	// Validate the loaded map
	if (!check_map_validity(game->map))
		return (1);

	// Set window size
	game->mlx->win_width = 1024;
	game->mlx->win_height = 768;

	if (init_window(game))
		return (1);

	// Load textures (fallback to colors if failed)
	if (load_textures(game))
		ft_printf("Warning: Textures not loaded.\n");

	// Ensure `game->map->map_array` exists before rendering
	if (!game->map->map_array)
		return (ft_printf("Error\nInvalid map array.\n"), 1);

	render_map(game);
	return (0);
}

int main(int argc, char **argv)
{
	t_game *game;

	game = ft_calloc(1, sizeof(t_game));
	if (!game)
		return (ft_printf("Error\nAllocation failed.\n"), 1);

	/* If init_all fails, close_game will free and exit. */
	if (init_all(game, argc, argv))
		return (close_game(game));

	/* Key hook to catch W,A,S,D or ESC */
	mlx_key_hook(game->mlx->win, handle_keypress, game);

	/* Hook for window close button (button X) */
	mlx_hook(game->mlx->win, 17, 0, close_game, game);


	//mlx_hook(game->mlx->win, ConfigureNotify, StructureNotifyMask, resize_hook, game);

	mlx_loop(game->mlx->id);
	return (close_game(game));
}
