/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monster_movement.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anebbou <anebbou@student42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 10:00:00 by anebbou           #+#    #+#             */
/*   Updated: 2025/02/15 15:48:39 by anebbou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* Helper function to move a single monster with Option A */
static void	move_monster(t_game *game, int x, int y)
{
	int		new_x;
	int		new_y;
	int		valid_dirs[4];
	int		count;
	int		direction;
	char	tile;
	char	dest;

	new_x = x;
	new_y = y;
	count = 0;
	if (x > 0)
	{
		tile = game->map->map_array[x - 1][y];
		if (tile == '0' || tile == 'C' || tile == 'P')
			valid_dirs[count++] = 0;
	}
	if (x < game->map->height - 1)
	{
		tile = game->map->map_array[x + 1][y];
		if (tile == '0' || tile == 'C' || tile == 'P')
			valid_dirs[count++] = 1;
	}
	if (y > 0)
	{
		tile = game->map->map_array[x][y - 1];
		if (tile == '0' || tile == 'C' || tile == 'P')
			valid_dirs[count++] = 2;
	}
	if (y < game->map->width - 1)
	{
		tile = game->map->map_array[x][y + 1];
		if (tile == '0' || tile == 'C' || tile == 'P')
			valid_dirs[count++] = 3;
	}
	if (count == 0)
		return ;
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
	if (game->map->map_array[new_x][new_y] == 'P')
	{
		lose_game(game);
		return ;
	}
	dest = game->map->map_array[new_x][new_y];
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
void	move_monsters(t_game *game)
{
	int	x;
	int	y;

	x = 0;
	while (x < game->map->height)
	{
		y = 0;
		while (y < game->map->width)
		{
			if (game->map->map_array[x][y] == 'M' ||
				game->map->map_array[x][y] == 'm')
			{
				move_monster(game, x, y);
			}
			y++;
		}
		x++;
	}
	render_map(game);
}
