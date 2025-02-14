#include "so_long.h"

/* Initialize the MLX library */
int init_mlx(t_game *game)
{
	ft_printf("DEBUG: Allocating MLX struct\n");
	game->mlx = ft_calloc(1, sizeof(t_mlx));
	if (!game->mlx)
		return (ft_printf("Error\nFailed to allocate t_mlx.\n"), 1);

	ft_printf("DEBUG: Initializing MLX\n");
	game->mlx->id = mlx_init();
	if (!game->mlx->id)
		return (ft_printf("Error\nmlx_init() failed.\n"), 1);

	return (0);
}
