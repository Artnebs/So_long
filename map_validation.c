/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anebbou <anebbou@student42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 10:00:00 by anebbou           #+#    #+#             */
/*   Updated: 2025/02/28 13:19:33 by anebbou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	fill_map_dimensions(t_map *map_data)
{
	int	i;
	int	len;

	i = 0;
	while (map_data->map_array[i])
	{
		len = ft_strlen(map_data->map_array[i]);
		while (len > 0 && (map_data->map_array[i][len - 1] == '\n'
			|| map_data->map_array[i][len - 1] == '\r'))
		{
			map_data->map_array[i][len - 1] = '\0';
			len--;
		}
		i++;
	}
	map_data->height = i;
	if (map_data->height == 0)
	{
		ft_printf("Error\nEmpty map.\n");
		return (0);
	}
	map_data->width = ft_strlen(map_data->map_array[0]);
	return (1);
}

int	check_rectangle(t_map *map_data)
{
	int	i;
	int	width;

	width = ft_strlen(map_data->map_array[0]);
	i = 1;
	while (i < map_data->height)
	{
		if ((int)ft_strlen(map_data->map_array[i]) != width)
		{
			ft_printf("Error\nMap is not a rectangle.\n");
			return (0);
		}
		i++;
	}
	return (1);
}

int	check_walls(t_map *map_data)
{
	int	i;

	i = 0;
	while (i < map_data->width)
	{
		if (map_data->map_array[0][i] != '1'
			|| map_data->map_array[map_data->height - 1][i] != '1')
		{
			ft_printf("Error\nMap is not surrounded by walls.\n");
			return (0);
		}
		i++;
	}
	i = 0;
	while (i < map_data->height)
	{
		if (map_data->map_array[i][0] != '1'
			|| map_data->map_array[i][map_data->width - 1] != '1')
		{
			ft_printf("Error\nMap is not surrounded by walls.\n");
			return (0);
		}
		i++;
	}
	return (1);
}

int	check_chars_count(t_map *map_data)
{
	int	player_count;
	int	exit_count;
	int	collect_count;

	player_count = 0;
	exit_count = 0;
	collect_count = 0;
	count_chars(map_data, &player_count, &exit_count, &collect_count);
	if (player_count != 1 || exit_count != 1 || collect_count < 1)
	{
		ft_printf("Error\nInvalid number of characters.\n");
		return (0);
	}
	map_data->player_count = player_count;
	map_data->exit_count = exit_count;
	map_data->collect_count = collect_count;
	return (1);
}

int	check_map_validity(t_map *map_data)
{
	if (!map_data->map_array)
	{
		ft_printf("Error\nInvalid map array.\n");
		return (0);
	}
	if (!fill_map_dimensions(map_data))
		return (0);
	if (!check_rectangle(map_data))
		return (0);
	if (!check_walls(map_data))
		return (0);
	if (!check_chars_count(map_data))
		return (0);
	if (!check_path(map_data))
		return (0);
	return (1);
}
