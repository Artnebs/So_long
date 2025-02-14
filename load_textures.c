#include "so_long.h"

static void *load_texture(void *mlx, char *path)
{
    void *img;
    int width;
    int height;

    img = mlx_xpm_file_to_image(mlx, path, &width, &height);
    if (!img)
        ft_printf("Error\nFailed to load texture: %s\n", path);
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

    if (!game->textures->wall || !game->textures->floor || !game->textures->player ||
        !game->textures->collectible || !game->textures->exit || !game->textures->monster)
    {
        free_textures(game);
        return (ft_printf("Error\nFailed to load one or more textures.\n"), 1);
    }

    return 0;
}