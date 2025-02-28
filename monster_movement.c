/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monster_movement.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anebbou <anebbou@student42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 10:00:00 by anebbou           #+#    #+#             */
/*   Updated: 2025/02/28 14:06:09 by anebbou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	move_monster(t_game *game, int x, int y)
{
	int		valid_dirs[4];
	int		count;
	int		dir;
	int		nx;
	int		ny;

	count = collect_valid_directions(game, x, y, valid_dirs);
	if (count == 0)
		return ;
	dir = valid_dirs[rand() % count];
	nx = x;
	ny = y;
	update_coordinates(dir, &nx, &ny);
	if (game->map->map_array[nx][ny] == 'P')
		return (lose_game(game));
	update_monster_position(game, x, y, dir);
}

void	move_monsters(t_game *game)
{
	int	x;
	int	y;

	x = game->map->height - 1;
	while (x >= 0)
	{
		y = game->map->width - 1;
		while (y >= 0)
		{
			if (game->map->map_array[x][y] == 'M')
			{
				move_monster(game, x, y);
			}
			y--;
		}
		x--;
	}
	render_map(game);
}
