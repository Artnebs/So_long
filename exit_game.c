#include "so_long.h"

/*
** free_textures:
** - Destroys each texture if not NULL.
** - Frees the textures struct.
*/
void free_textures(t_game *game)
{
    if (!game->textures)
        return;
    if (game->textures->wall)
        mlx_destroy_image(game->mlx->id, game->textures->wall);
    if (game->textures->floor)
        mlx_destroy_image(game->mlx->id, game->textures->floor);
    if (game->textures->player)
        mlx_destroy_image(game->mlx->id, game->textures->player);
    if (game->textures->collectible)
        mlx_destroy_image(game->mlx->id, game->textures->collectible);
    if (game->textures->exit)
        mlx_destroy_image(game->mlx->id, game->textures->exit);
    free(game->textures);
    game->textures = NULL;
}


/*
** close_game:
**  - Stops background music.
**  - Frees all allocated memory and closes the window.
**  - Returns 0 for proper MLX callback handling.
*/
int close_game(t_game *game)
{
	if (!game)
		exit(0);

	stop_background_music(); // Stop music

	if (game->mlx)
	{
		if (game->mlx->win)
			mlx_destroy_window(game->mlx->id, game->mlx->win);
		free_textures(game);
	}
	if (game->map)
	{
		free_map(game->map->map_array);
		free(game->map);
		game->map = NULL;
	}
	if (game->mlx)
	{
		free(game->mlx);
		game->mlx = NULL;
	}
	free(game);
	exit(0);
	return (0);
}

/*
** win_game:
**  - Called when the player reaches exit with all collectibles collected.
**  - Print "You win!" and close the game properly.
*/
void win_game(t_game *game)
{
    ft_printf("You win!\n");
    close_game(game);
}
