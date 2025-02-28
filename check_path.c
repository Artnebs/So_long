/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anebbou <anebbou@student42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 10:00:00 by anebbou           #+#    #+#             */
/*   Updated: 2025/02/28 12:59:58 by anebbou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	find_player_pos(t_map *map_data, int *p_x, int *p_y)
{
	if (map_data->player_count != 1)
	{
		ft_printf("Error\nNo valid player found.\n");
		return (0);
	}
	*p_x = map_data->player_x;
	*p_y = map_data->player_y;
	return (1);
}

static char	**duplicate_map(char **map_array, int height)
{
	char	**copy;
	int		i;

	copy = malloc(sizeof(char *) * (height + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < height)
	{
		copy[i] = ft_strdup(map_array[i]);
		if (!copy[i])
		{
			free_map(copy);
			return (NULL);
		}
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

static void	flood_fill(char **map_copy, int x, int y, t_map *map_data)
{
	if (x < 0 || y < 0 || x >= map_data->height || y >= map_data->width)
		return ;
	if (map_copy[x][y] == '1' || map_copy[x][y] == 'X')
		return ;
	map_copy[x][y] = 'X';
	flood_fill(map_copy, x - 1, y, map_data);
	flood_fill(map_copy, x + 1, y, map_data);
	flood_fill(map_copy, x, y - 1, map_data);
	flood_fill(map_copy, x, y + 1, map_data);
}

static int	verify_reachable(char **map_copy, t_map *map_data)
{
	int	i;
	int	j;

	i = 0;
	while (i < map_data->height)
	{
		j = 0;
		while (j < map_data->width)
		{
			if (map_data->map_array[i][j] == 'C'
					|| map_data->map_array[i][j] == 'E')
			{
				if (map_copy[i][j] != 'X')
				{
					ft_printf("Error\nUnreachable C/E at (%d,%d).\n", i, j);
					return (0);
				}
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	check_path(t_map *map_data)
{
	char	**map_copy;
	int		p_x;
	int		p_y;

	if (!find_player_pos(map_data, &p_x, &p_y))
		return (0);
	map_copy = duplicate_map(map_data->map_array, map_data->height);
	if (!map_copy)
	{
		ft_printf("Error\nFailed to copy map.\n");
		return (0);
	}
	flood_fill(map_copy, p_x, p_y, map_data);
	if (!verify_reachable(map_copy, map_data))
	{
		free_map(map_copy);
		return (0);
	}
	free_map(map_copy);
	return (1);
}
