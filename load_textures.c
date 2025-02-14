#include "so_long.h"

static void *load_texture(void *mlx, char *path)
{
	void *img;
	int width;
	int height;

	img = mlx_xpm_file_to_image(mlx, path, &width, &height);
	if (!img)
		ft_printf("Warning\nFailed to load texture: %s\n", path);
	return img;
}

int load_textures(t_game *game)
{
	game->textures = ft_calloc(1, sizeof(t_textures));
	if (!game->textures)
		return (ft_printf("Error\nFailed to allocate textures struct.\n"), 1);

	game->textures->wall = load_texture(game->mlx->id, "textures/wall.xpm");
	game->textures->floor = load_texture(game->mlx->id, "textures/floor.xpm");
	game->textures->player = load_texture(game->mlx->id, "textures/player.xpm");
	game->textures->collectible = load_texture(game->mlx->id, "textures/collectible.xpm");
	game->textures->exit = load_texture(game->mlx->id, "textures/exit.xpm");
	game->textures->monster = load_texture(game->mlx->id, "textures/monster.xpm");

	/*
	** If absolutely all textures failed, we can warn the user
	** that only fallback colors will be drawn.
	*/
	if (!game->textures->wall && !game->textures->floor &&
		!game->textures->player && !game->textures->collectible &&
		!game->textures->exit && !game->textures->monster)
	{
		ft_printf("Warning\nAll textures failed to load; fallback colors only.\n");
	}

	return (0);
}
