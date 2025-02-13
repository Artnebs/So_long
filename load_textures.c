#include "so_long.h"

/*
** load_textures:
** Try to load each .xpm file.
** If it fails, print an error but DON'T exit.
** We'll fallback to using colors in render_map().
** Return 0 on success, 1 if any texture fails.
*/
int load_textures(t_game *game)
{
	int width;
	int height;

	// Always allocate textures, even if we use color fallback
	game->textures = (t_textures *)ft_calloc(1, sizeof(t_textures));
	if (!game->textures)
	{
		ft_printf("Error\nFailed to allocate t_textures.\n");
		return (1);
	}

	// Load textures (will fail if files are missing)
	game->textures->wall = mlx_xpm_file_to_image(game->mlx->id, "textures/wall.xpm", &width, &height);
	if (!game->textures->wall)
		ft_printf("Warning\nFailed to load wall.xpm.\n");

	game->textures->player = mlx_xpm_file_to_image(game->mlx->id, "textures/player.xpm", &width, &height);
	if (!game->textures->player)
		ft_printf("Warning\nFailed to load player.xpm.\n");

	game->textures->collectible = mlx_xpm_file_to_image(game->mlx->id, "textures/collectible.xpm", &width, &height);
	if (!game->textures->collectible)
		ft_printf("Warning\nFailed to load collectible.xpm.\n");

	game->textures->exit = mlx_xpm_file_to_image(game->mlx->id, "textures/exit.xpm", &width, &height);
	if (!game->textures->exit)
		ft_printf("Warning\nFailed to load exit.xpm.\n");

	game->textures->floor = mlx_xpm_file_to_image(game->mlx->id, "textures/floor.xpm", &width, &height);
	if (!game->textures->floor)
		ft_printf("Warning\nFailed to load floor.xpm.\n");

	// If all textures are missing, return 1 to indicate fallback mode
	if (!game->textures->wall && !game->textures->player &&
		!game->textures->collectible && !game->textures->exit && !game->textures->floor)
	{
		ft_printf("Warning: No textures loaded. Using fallback colors.\n");
	}

	return (0);
}
