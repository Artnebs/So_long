/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monster_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anebbou <anebbou@student42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 13:02:02 by anebbou           #+#    #+#             */
/*   Updated: 2025/02/28 14:06:35 by anebbou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	is_movable(t_game *game, int x, int y)
{
	char	tile;

	tile = game->map->map_array[x][y];
	return (tile == '0' || tile == 'C' || tile == 'P');
}

int	collect_valid_directions(t_game *game, int x, int y, int dirs[4])
{
	int	count;

	count = 0;
	if (x > 0 && is_movable(game, x - 1, y))
		dirs[count++] = 0;
	if (x < game->map->height - 1 && is_movable(game, x + 1, y))
		dirs[count++] = 1;
	if (y > 0 && is_movable(game, x, y - 1))
		dirs[count++] = 2;
	if (y < game->map->width - 1 && is_movable(game, x, y + 1))
		dirs[count++] = 3;
	return (count);
}

void	update_coordinates(int direction, int *nx, int *ny)
{
	if (direction == 0)
		*nx -= 1;
	else if (direction == 1)
		*nx += 1;
	else if (direction == 2)
		*ny -= 1;
	else if (direction == 3)
		*ny += 1;
}

void	update_monster_tile(t_game *game, int x, int y, char new_tile)
{
	if (new_tile == 'C')
		game->map->map_array[x][y] = 'm';
	else if (new_tile == '0')
		game->map->map_array[x][y] = 'M';
	else
		game->map->map_array[x][y] = new_tile;
}

void	update_monster_position(t_game *game, int x, int y, int direction)
{
	int	nx;
	int	ny;

	nx = x;
	ny = y;
	update_coordinates(direction, &nx, &ny);
	game->map->map_array[x][y] = '0';
	update_monster_tile(game, nx, ny, game->map->map_array[nx][ny]);
}
