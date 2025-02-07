/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anebbou <anebbou@student42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:35:33 by anebbou           #+#    #+#             */
/*   Updated: 2025/02/04 15:56:12 by anebbou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int main(int argc, char **argv)
{
	t_map map_data;

	if (argc != 2)
		return (ft_printf("Usage: ./so_long map.ber\n"), 1);
	ft_bzero(&map_data, sizeof(t_map));
	map_data.map_array = read_map_file(argv[1]);
	if (!map_data.map_array)
		return (1);
	if (!check_map_validity(&map_data))
	{
		free_map(map_data.map_array);
		return (1);
	}
	ft_printf("Map validated successfully!\n");

	/* -- Initialize window & load textures -- */
	if (!init_window(&map_data))
	{
		free_map(map_data.map_array);
		return (1);
	}

	/* -- Render the map once -- */
	render_map(&map_data);

	/* -- Hook your key events + close events -- */
	mlx_key_hook(map_data.win, handle_keypress, &map_data); // We'll code 'handle_keypress' soon
	mlx_hook(map_data.win, 17, 0, close_game, &map_data);	// 17 is the "destroy window" event on Linux

	/* -- Start the MLX event loop -- */
	mlx_loop(map_data.mlx);

	free_map(map_data.map_array);
	return (0);
}
