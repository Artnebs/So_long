/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   music.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anebbou <anebbou@student42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 10:00:00 by anebbou           #+#    #+#             */
/*   Updated: 2025/02/15 15:06:58 by anebbou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void play_background_music(void)
{
	system("mpg123 -q --loop -1 " MP3_FILE " &");
}

void stop_background_music(void)
{
	system("pkill -f mpg123");
}

void toggle_music(t_game *game)
{
	if (game->mute)
	{
		play_background_music();
		game->mute = 0;
	}
	else
	{
		stop_background_music();
		game->mute = 1;
	}
}
