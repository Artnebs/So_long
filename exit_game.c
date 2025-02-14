#include "so_long.h"

/* Free all textures if they exist */
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
	if (game->textures->monster)
		mlx_destroy_image(game->mlx->id, game->textures->monster);
	free(game->textures);
	game->textures = NULL;
}

/* Close the game, free all resources, and exit */
int close_game(t_game *game)
{
	if (!game)
		exit(0);
	stop_background_music();
	if (game->mlx && game->mlx->win)
		mlx_destroy_window(game->mlx->id, game->mlx->win);
	free_textures(game);
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

/* Called when you reach 'E' with all collectibles */
void win_game(t_game *game)
{
	ft_printf("You win!\n");
	close_game(game);
}
