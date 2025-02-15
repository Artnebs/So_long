#include "so_long.h"

void check_textures(t_game *game)
{
    if (!game->textures)
        return;
    if (!game->textures->wall)
        ft_printf("ERROR: Missing texture: wall\n");
    if (!game->textures->player)
        ft_printf("ERROR: Missing texture: player\n");
    if (!game->textures->collectible)
        ft_printf("ERROR: Missing texture: collectible\n");
    if (!game->textures->exit)
        ft_printf("ERROR: Missing texture: exit\n");
    if (!game->textures->floor)
        ft_printf("ERROR: Missing texture: floor\n");
    if (!game->textures->monster)
        ft_printf("ERROR: Missing texture: monster\n");
}
