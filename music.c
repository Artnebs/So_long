#include "so_long.h"

void play_background_music(void)
{
	/* Loop the specified MP3 in the background using mpg123 */
	system("mpg123 -q --loop -1 " MP3_FILE " &");
}

void stop_background_music(void)
{
	/* Kill mpg123 process */
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
