#include "so_long.h"

/*
** load_textures:
**  - Loads each .xpm file for textures.
**  - If a file is missing, prints a warning but doesn't crash.
*/
int load_textures(t_game *game)
{
	int width;
	int height;

	game->textures = (t_textures *)ft_calloc(1, sizeof(t_textures));
	if (!game->textures)
	{
		ft_printf("Error\nFailed to allocate textures.\n");
		return (1);
	}

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

	game->textures->monster = mlx_xpm_file_to_image(game->mlx->id, "textures/monster.xpm", &width, &height);
	if (!game->textures->monster)
		ft_printf("Warning\nFailed to load monster.xpm.\n");

	if (!game->textures->wall && !game->textures->player &&
		!game->textures->collectible && !game->textures->exit &&
		!game->textures->floor && !game->textures->monster)
	{
		ft_printf("Warning: No textures loaded. Using fallback colors.\n");
	}

	return (0);
}
