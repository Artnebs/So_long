#include "so_long.h"

/* Local function: chain of init calls before the MLX loop */
static int init_all(t_game *game, int argc, char **argv)
{
	int parse_ok;

	ft_printf("DEBUG: Initializing MLX\n");
	if (init_mlx(game))
		return (1);

	if (argc == 2)
	{
		ft_printf("DEBUG: Parsing map file %s\n", argv[1]);
		parse_ok = parse_map(game, argv[1]);
		if (!parse_ok)
			return (1);
	}
	else
	{
		ft_printf("No map provided, using default map.\n");
		load_default_map(game);
	}

	ft_printf("DEBUG: Checking map validity\n");
	if (!check_map_validity(game->map))
		return (1);

	ft_printf("DEBUG: Initializing window\n");
	if (init_window(game))
		return (1);

	ft_printf("DEBUG: Loading textures\n");
	if (load_textures(game))
		ft_printf("Warning: Textures not loaded.\n");

	ft_printf("DEBUG: Checking textures\n");
	check_textures(game);

	ft_printf("DEBUG: Rendering map\n");
	render_map(game);

	return (0);
}

/* The main entry point */
int main(int argc, char **argv)
{
	t_game *game;

	ft_printf("DEBUG: Starting program\n");
	game = ft_calloc(1, sizeof(t_game));
	if (!game)
		return (ft_printf("Error\nAllocation failed.\n"), 1);

	ft_printf("DEBUG: Game struct allocated\n");

	if (init_all(game, argc, argv))
		return (close_game(game));

	ft_printf("DEBUG: Game initialized successfully\n");

	play_background_music();
	ft_printf("DEBUG: Music started\n");

	mlx_key_hook(game->mlx->win, handle_keypress, game);
	mlx_hook(game->mlx->win, 17, 0, close_game, game);

	ft_printf("DEBUG: Entering MLX loop\n");
	mlx_loop(game->mlx->id);

	ft_printf("DEBUG: Exiting MLX loop\n");
	stop_background_music();

	return (close_game(game));
}
