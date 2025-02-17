/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anebbou <anebbou@student42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 10:00:00 by anebbou           #+#    #+#             */
/*   Updated: 2025/02/15 15:39:07 by anebbou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
/* Free a map array */
void free_map(char **map_array)
{
	int i;

	if (!map_array)
		return;
	i = 0;
	while (map_array[i])
	{
		free(map_array[i]);
		i++;
	}
	free(map_array);
}
