#include "so_long.h"

/* Initialize the MLX library */
int init_mlx(t_game *game)
{
    game->mlx = ft_calloc(1, sizeof(t_mlx));
    if (!game->mlx)
        return (ft_printf("Error\nFailed to allocate t_mlx.\n"), 1);

    game->mlx->id = mlx_init();
    if (!game->mlx->id)
        return (ft_printf("Error\nmlx_init() failed.\n"), 1);

    return (0);
}
