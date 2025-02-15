#include "so_long.h"

/* Local function: chain of init calls before the MLX loop */
static int init_all(t_game *game, int argc, char **argv)
{
    int parse_ok;

    if (init_mlx(game))
        return (1);

    if (argc == 2)
    {
        parse_ok = parse_map(game, argv[1]);
        if (!parse_ok)
            return (1);
    }
    else
    {
        load_default_map(game);
    }

    if (!check_map_validity(game->map))
        return (1);

    if (init_window(game))
        return (1);

    if (load_textures(game))
        ft_printf("Warning: Textures not loaded.\n");

    check_textures(game);

    render_map(game);

    return (0);
}

/* The main entry point */
int main(int argc, char **argv)
{
    t_game *game;

    game = ft_calloc(1, sizeof(t_game));
    if (!game)
        return (ft_printf("Error\nAllocation failed.\n"), 1);

    if (init_all(game, argc, argv))
        return (close_game(game));

    play_background_music();

    mlx_key_hook(game->mlx->win, handle_keypress, game);
    mlx_hook(game->mlx->win, 17, 0, close_game, game);

    mlx_loop(game->mlx->id);

    stop_background_music();

    return (close_game(game));
}
