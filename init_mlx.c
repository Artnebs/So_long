/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anebbou <anebbou@student42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 10:00:00 by anebbou           #+#    #+#             */
/*   Updated: 2025/02/28 13:16:07 by anebbou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	init_mlx(t_game *game)
{
	game->mlx = ft_calloc(1, sizeof(t_mlx));
	if (!game->mlx)
	{
		ft_printf("Error\nFailed to allocate t_mlx.\n");
		return (1);
	}
	game->mlx->id = mlx_init();
	if (!game->mlx->id)
	{
		ft_printf("Error\nmlx_init() failed.\n");
		return (1);
	}
	return (0);
}
