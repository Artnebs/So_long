#ifndef SO_LONG_H
#define SO_LONG_H

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <X11/Xlib.h> // or relevant for Linux
#include <mlx.h>
#include "libft.h"           // For ft_printf, etc.


/*
** KEYCODES - adapt if on Linux or macOS
*/
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
#define KEY_M 109
#endif

#ifndef HUD_HEIGHT
#define HUD_HEIGHT 40
#endif

/*
** TILE_SIZE, COLORS
*/
#define TILE_SIZE 64
#define COLOR_WALL 0xAAAAAA
#define COLOR_PLAYER 0xFF0000
#define COLOR_COLLECT 0x0000FF
#define COLOR_EXIT 0x00FF00
#define COLOR_MONSTER 0xFF00FF
#define COLOR_FLOOR 0xFFFFFF

/*
** MP3 FILE for background music (if used)
*/
#define MP3_FILE "music/music.mp3"

/*
** STRUCTS
*/
typedef struct s_textures
{
    void *wall;
    void *floor;
    void *player;
    void *collectible;
    void *exit;
    void *monster;
    void *hud_moves;
    void *hud_collect;
    void *hud_lives;
} t_textures;

typedef struct s_map
{
    char **map_array;
    int width;
    int height;
    int player_count;
    int exit_count;
    int collect_count;
    int player_x;
    int player_y;
    int player_lives;
    int moves;
    int spawn_x; // Added spawn_x
    int spawn_y; // Added spawn_y
} t_map;

typedef struct s_mlx
{
    void *id;
    void *win;
    int win_width;
    int win_height;
} t_mlx;

typedef struct s_game
{
    t_mlx *mlx;
    t_map *map;
    t_textures *textures;
    int mute; // Added mute flag for music
} t_game;

/*
** FUNCTION PROTOTYPES
*/

/* check_path.c */
int check_path(t_map *map_data);

/* check_textures.c */
void check_textures(t_game *game);

/* exit_game.c */
void free_textures(t_game *game);
int close_game(t_game *game);
void win_game(t_game *game);

/* init_mlx.c */
int init_mlx(t_game *game);
int init_window(t_game *game);

/* load_default_map.c */
void load_default_map(t_game *game);

/* load_textures.c */
int load_textures(t_game *game);

/* main.c */
int main(int argc, char **argv);

/* map_parsing.c */
char **read_map_file(char *filename);
void free_map(char **map_array);
int parse_map(t_game *game, char *filename);

/* map_validation.c */
int check_map_validity(t_map *map_data);
int check_rectangle(t_map *map_data);
int check_walls(t_map *map_data);
int check_chars_count(t_map *map_data);

/* monster_movement.c */
void move_monsters(t_game *game);

/* music.c */
void play_background_music(void);
void stop_background_music(void);
void toggle_music(t_game *game);

/* player_movement.c */
void move_player(t_game *game, int dx, int dy);
void lose_game(t_game *game);
int handle_keypress(int keycode, t_game *game);
void respawn_player(t_game *game);

/* render_map.c */
void render_map(t_game *game);
void put_texture_tile(t_game *game, int y, int x, char c);
void render_hud(t_game *game); // Added function prototype

/* resize_hook.c */
int resize_hook(int width, int height, t_game *game);

#endif
