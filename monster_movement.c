#include "so_long.h"

/* Helper function to move a single monster */
static void move_monster(t_game *game, int x, int y)
{
    int new_x = x;
    int new_y = y;
    int direction = rand() % 4;

    if (direction == 0 && x > 0) // Move up
        new_x--;
    else if (direction == 1 && x < game->map->height - 1) // Move down
        new_x++;
    else if (direction == 2 && y > 0) // Move left
        new_y--;
    else if (direction == 3 && y < game->map->width - 1) // Move right
        new_y++;

    if (game->map->map_array[new_x][new_y] == '0' || game->map->map_array[new_x][new_y] == 'P')
    {
        if (game->map->map_array[new_x][new_y] == 'P')
        {
            lose_game(game);
        }
        game->map->map_array[x][y] = '0';
        game->map->map_array[new_x][new_y] = 'M';
    }
}

/* Move all monsters in the game */
void move_monsters(t_game *game)
{
    int x;
    int y;

    for (x = 0; x < game->map->height; x++)
    {
        for (y = 0; y < game->map->width; y++)
        {
            if (game->map->map_array[x][y] == 'M')
            {
                move_monster(game, x, y);
            }
        }
    }
    render_map(game);
}