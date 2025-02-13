#ifndef SO_LONG_H
#define SO_LONG_H

/* ------------- INCLUDES ------------- */
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <X11/Xlib.h>
#include <mlx.h>		   // MiniLibX
#include "libft.h"		   // Your libft (ft_printf, ft_strlen, etc.)
#include "get_next_line.h" // get_next_line
/* ------------------------------------ */

/* ------------- DEFINES -------------- */
// Keycodes (adapt as needed for your OS)
#ifdef __APPLE__
#define KEY_ESC 53
#define KEY_W 13
#define KEY_A 0
#define KEY_S 1
#define KEY_D 2
#else
#define KEY_ESC 65307
#define KEY_W 119
#define KEY_A 97
#define KEY_S 115
#define KEY_D 100
#endif

// Tile size in pixels
#define TILE_SIZE 32
#define MP3_FILE "music/Cornfield_Chase_Interstellar_Soundtrack-643446-mobiles24.mp3"


// Colors (for placeholder rendering)
#define COLOR_WALL 0xAAAAAA	   // Gray
#define COLOR_PLAYER 0xFF0000  // Red
#define COLOR_COLLECT 0x0000FF // Blue
#define COLOR_EXIT 0x00FF00	   // Green
#define COLOR_FLOOR 0xFFFFFF   // White
#define COLOR_MONSTER 0xFFA500 // Orange (New: Monster fallback color)

#define WALL_TEXTURE "textures/wall.xpm"
#define PLAYER_TEXTURE "textures/player.xpm"
#define COLLECTIBLE_TEXTURE "textures/collectible.xpm"
#define EXIT_TEXTURE "textures/exit.xpm"
#define FLOOR_TEXTURE "textures/floor.xpm"
#define MONSTER_TEXTURE "textures/monster.xpm" // New: Monster texture

/* ------------------------------------ */

/* ------------- STRUCTS -------------- */

// Forward declarations
struct s_game;
struct s_mlx;
struct s_map;
struct s_textures;

/*
** t_textures:
** Holds optional texture pointers.
** They may remain NULL if loading fails or if you're only using colors.
*/
typedef struct s_textures
{
	void *wall;
	void *floor;
	void *player;
	void *collectible;
	void *exit;
	void *monster; // New: Monster texture
} t_textures;

/*
** t_map:
** Holds the 2D map array and its dimensions,
** plus counters for players, exits, collectibles.
*/
typedef struct s_map
{
	char **map_array;
	int width;
	int height;
	int player_count;
	int exit_count;
	int collect_count;
	int player_x;	  // Player position (row)
	int player_y;	  // Player position (col)
	int moves;		  // Count movements
	int player_lives; // New: Player lives
} t_map;

/*
** t_mlx:
** Holds the MLX instance + window pointer.
*/
typedef struct s_mlx
{
	void *id;
	void *win;
	int win_width;
	int win_height;
} t_mlx;

/*
** t_game:
** Main game struct that wraps all other data.
*/
typedef struct s_game
{
	t_mlx *mlx;
	t_map *map;
	t_textures *textures;
} t_game;

/* --------- FUNCTION PROTOTYPES ------ */

/* so_long.c */
int main(int argc, char **argv);

void play_background_music();
void stop_background_music();

/* init_mlx.c */
int init_mlx(t_game *game);
int init_window(t_game *game);

/* load_textures.c */
int load_textures(t_game *game);

/* map_parsing.c */
char **read_map_file(char *filename);
void free_map(char **map_array);
int parse_map(t_game *game, char *filename);
void place_collectibles_randomly(t_game *game, int num_collectibles);

/* map_validation.c */
int check_map_validity(t_map *map_data);
int check_rectangle(t_map *map_data);
int check_walls(t_map *map_data);
int check_chars_count(t_map *map_data);

/* check_path.c */
int check_path(t_map *map_data);

/* render_map.c */
void render_map(t_game *game);
void draw_tile(t_game *game, int x, int y, int color);
void load_default_map(t_game *game);
int resize_hook(int width, int height, t_game *game);

/* player_movement.c */
int handle_keypress(int keycode, t_game *game);
void move_player(t_game *game, int dx, int dy);

/* monster_movement.c */ // New: File for monster behavior
void move_monsters(t_game *game);
void lose_game(t_game *game); // Updated: Handle lives before losing

/* exit_game.c */
void free_textures(t_game *game);
int close_game(t_game *game);
void win_game(t_game *game);

#endif
