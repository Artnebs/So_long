#include "so_long.h"

/* Helper function to move a single monster with Option A */
static void move_monster(t_game *game, int x, int y)
{
    int new_x = x;
    int new_y = y;
    int valid_dirs[4];
    int count = 0;
    int direction;

    /* Gather valid directions:
       0: up, 1: down, 2: left, 3: right */
    if (x > 0)
    {
        char tile = game->map->map_array[x - 1][y];
        if (tile == '0' || tile == 'C' || tile == 'P')
            valid_dirs[count++] = 0;
    }
    if (x < game->map->height - 1)
    {
        char tile = game->map->map_array[x + 1][y];
        if (tile == '0' || tile == 'C' || tile == 'P')
            valid_dirs[count++] = 1;
    }
    if (y > 0)
    {
        char tile = game->map->map_array[x][y - 1];
        if (tile == '0' || tile == 'C' || tile == 'P')
            valid_dirs[count++] = 2;
    }
    if (y < game->map->width - 1)
    {
        char tile = game->map->map_array[x][y + 1];
        if (tile == '0' || tile == 'C' || tile == 'P')
            valid_dirs[count++] = 3;
    }
    if (count == 0)
        return; // no valid move available

    direction = valid_dirs[rand() % count];

    if (direction == 0)
    {
        new_x = x - 1;
        new_y = y;
    }
    else if (direction == 1)
    {
        new_x = x + 1;
        new_y = y;
    }
    else if (direction == 2)
    {
        new_x = x;
        new_y = y - 1;
    }
    else if (direction == 3)
    {
        new_x = x;
        new_y = y + 1;
    }

    /* If the destination is the player, lose the game */
    if (game->map->map_array[new_x][new_y] == 'P')
    {
        lose_game(game);
        return;
    }

    /* Determine the new destination tile:
       - If destination is 'C', we mark it as 'm' (monster on collectible)
         so that the collectible underneath is not removed.
       - Otherwise, if it’s '0', we mark it as 'M'. */
    char dest = game->map->map_array[new_x][new_y];

    /* Restore current tile:
       - If the monster is leaving a tile that was marked 'm', restore 'C'
         (collectible remains); otherwise, set to '0'. */
    if (game->map->map_array[x][y] == 'm')
        game->map->map_array[x][y] = 'C';
    else
        game->map->map_array[x][y] = '0';

    if (dest == 'C')
        game->map->map_array[new_x][new_y] = 'm';
    else
        game->map->map_array[new_x][new_y] = 'M';
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
            if (game->map->map_array[x][y] == 'M' ||
                game->map->map_array[x][y] == 'm')
            {
                move_monster(game, x, y);
            }
        }
    }
    render_map(game);
}
