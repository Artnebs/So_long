/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anebbou <anebbou@student42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 12:38:25 by anebbou           #+#    #+#             */
/*   Updated: 2025/02/04 16:39:39 by anebbou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
#define SO_LONG_H

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "libft.h"
#include "mlx.h"

#define TILE_SIZE 32

typedef struct s_map
{
    char **map_array;
    int width;
    int height;
    int player_count;
    int exit_count;
    int collect_count;

    /* MLX pointers */
    void *mlx;
    void *win;

    /* Images for each tile */
    void *tex_wall;
    void *tex_floor;
    void *tex_player;
    void *tex_player2; /* optional second frame for animation */
    void *tex_collect;
    void *tex_exit;
    void *tex_monster;

    /* Player position & moves */
    int player_x;
    int player_y;
    int moves;

    /* ... any other fields as needed ... */

} t_map;

/* Parsing & Validation */
char **read_map_file(char *filename);
int check_map_validity(t_map *map_data);
void free_map(char **map_array);

/* Validation Helpers */
int check_rectangle(t_map *map_data);
int check_walls(t_map *map_data);
int check_chars_count(t_map *map_data);
int check_path(t_map *map_data);

/* Initialization */
int init_window(t_map *map_data);
int load_textures(t_map *map_data);

/* Rendering */
int render_map(t_map *map_data);

/* Player Movement */
int handle_keypress(int keycode, t_map *map_data);
void move_player(t_map *map_data, int dx, int dy);

/* Game Exit */
int close_game(t_map *map_data);

#endif