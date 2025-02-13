#include "so_long.h"

/*
** play_background_music:
**  - Uses system() to play the MP3 file in the background on repeat.
**  - Requires `mpg123` installed.
*/
void play_background_music()
{
	system("mpg123 -q --loop -1 " MP3_FILE " &");
}

/*
** stop_background_music:
**  - Kills all `mpg123` processes when the game closes.
*/
void stop_background_music()
{
	system("pkill -f mpg123");
}

/*
** init_all:
**  - Initializes everything (MLX, map, textures).
**  - Ensures proper memory allocation.
**  - Handles fallback in case of errors.
*/
static int init_all(t_game *game, int argc, char **argv)
{
	if (init_mlx(game))
		return (1);

	game->map = ft_calloc(1, sizeof(t_map));
	if (!game->map)
		return (ft_printf("Error\nFailed to allocate t_map.\n"), 1);

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

	if (!check_map_validity(game->map))
		return (1);

	game->mlx->win_width = 1024;
	game->mlx->win_height = 768;

	if (init_window(game))
		return (1);

	if (load_textures(game))
		ft_printf("Warning: Textures not loaded.\n");

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

	if (init_all(game, argc, argv))
		return (close_game(game));

	play_background_music(); // Start music when game launches

	mlx_key_hook(game->mlx->win, handle_keypress, game);
	mlx_hook(game->mlx->win, 17, 0, close_game, game);

	mlx_loop(game->mlx->id);

	stop_background_music(); // Stop music on game exit
	return (close_game(game));
}
