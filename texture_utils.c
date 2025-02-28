/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anebbou <anebbou@student42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 10:00:00 by anebbou           #+#    #+#             */
/*   Updated: 2025/02/28 13:03:01 by anebbou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_textures(t_game *game)
{
	if (!game->textures)
		return ;
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

void	free_map(char **map_array)
{
	int	i;

	if (!map_array)
		return ;
	i = 0;
	while (map_array[i])
	{
		free(map_array[i]);
		i++;
	}
	free(map_array);
}

void	count_chars(t_map *map_data, int *player_count,
	int *exit_count, int *collect_count)
{
	int	i;
	int	j;

	i = 0;
	while (i < map_data->height)
	{
		j = 0;
		while (j < map_data->width)
		{
			if (map_data->map_array[i][j] == 'P')
			{
				map_data->player_x = i;
				map_data->player_y = j;
				(*player_count)++;
			}
			else if (map_data->map_array[i][j] == 'E')
				(*exit_count)++;
			else if (map_data->map_array[i][j] == 'C')
				(*collect_count)++;
			j++;
		}
		i++;
	}
}
