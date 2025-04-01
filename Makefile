# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anebbou <anebbou@student42.fr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/04 10:28:35 by anebbou           #+#    #+#              #
#    Updated: 2025/04/01 09:17:14 by anebbou          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ---------------------------------------------------------------------------- #
# PROGRAM NAME
# ---------------------------------------------------------------------------- #
NAME       = so_long

# ---------------------------------------------------------------------------- #
# DIRECTORIES & LIBRARIES
# ---------------------------------------------------------------------------- #
LIBFT_DIR  = Libft_GNL_Printf
LIBFT      = $(LIBFT_DIR)/libft.a
LIBFT_REPO = https://github.com/Artnebs/Libft_GNL_Printf.git

MLX_DIR    = minilibx-linux
MLX_LIB    = $(MLX_DIR)/libmlx.a

OBJ_DIR    = objs
SRC_DIR    = .

# ---------------------------------------------------------------------------- #
# COMPILER & FLAGS
# ---------------------------------------------------------------------------- #
CC         = gcc
CFLAGS     = -Wall -Wextra -Werror -g
INCLUDES   = -I. -I$(LIBFT_DIR)/includes -I$(MLX_DIR)

# ---------------------------------------------------------------------------- #
# SOURCE & OBJECT FILES
# ---------------------------------------------------------------------------- #
SRCS       = check_path.c exit_game.c init_mlx.c load_textures.c \
			 resize_hook.c init_window.c main.c map_parsing.c \
			 map_validation.c monster_movement.c music.c \
			 player_movement.c player_events.c render_map.c monster_helpers.c \
			 render_tile.c render_hud.c load_default_map.c texture_utils.c 

OBJS       = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

# ---------------------------------------------------------------------------- #
# DEFAULT RULE
# ---------------------------------------------------------------------------- #
all: $(NAME)

# ---------------------------------------------------------------------------- #
# CREATE OBJ DIRECTORY
# ---------------------------------------------------------------------------- #
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# ---------------------------------------------------------------------------- #
# COMPILE RULE FOR .c TO .o
# ---------------------------------------------------------------------------- #
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# ---------------------------------------------------------------------------- #
# BUILD so_long
# ---------------------------------------------------------------------------- #
$(NAME): $(LIBFT) $(MLX_LIB) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx \
		-lm -lXext -lX11 -o $(NAME)

# ---------------------------------------------------------------------------- #
# BUILD LIBFT
# ---------------------------------------------------------------------------- #
$(LIBFT):
	git clone $(LIBFT_REPO) $(LIBFT_DIR) || true
	make -C $(LIBFT_DIR)

# ---------------------------------------------------------------------------- #
# BUILD MINILIBX
# ---------------------------------------------------------------------------- #
$(MLX_LIB):
	make -C $(MLX_DIR)

# ---------------------------------------------------------------------------- #
# CLEAN OBJECT FILES
# ---------------------------------------------------------------------------- #
clean:
	rm -rf $(OBJ_DIR)
	make -C $(LIBFT_DIR) clean
	make -C $(MLX_DIR) clean

# ---------------------------------------------------------------------------- #
# CLEAN ALL GENERATED FILES + REMOVE LIBFT DIRECTORY
# ---------------------------------------------------------------------------- #
fclean: clean
	rm -f $(NAME)
	rm -rf $(LIBFT_DIR)

# ---------------------------------------------------------------------------- #
# REBUILD FROM SCRATCH
# ---------------------------------------------------------------------------- #
re: fclean all

# ---------------------------------------------------------------------------- #
# DEBUG MODE (WITH MINILIBX, WITH SANITIZER)
# ---------------------------------------------------------------------------- #
debug: fclean
	$(CC) $(CFLAGS) -fsanitize=address -o $(NAME)_debug \
		$(SRCS) -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx -lm -lXext -lX11

# ---------------------------------------------------------------------------- #
# RUN VALGRIND MEMORY CHECK (TOUS LES .ber)
# ---------------------------------------------------------------------------- #
valgrind: all
	bash test_so_long_clean.sh

# ---------------------------------------------------------------------------- #
# FULL PROJECT TEST (MAPS + LEAKS + SUMMARY)
# ---------------------------------------------------------------------------- #
test: all
	bash test_so_long_clean.sh > test_results.txt
	@echo "\n🔍 Résumé des fuites mémoire :"
	@grep "definitely lost" logs/*.filtered.log || echo "✅ Aucun problème détecté dans les logs filtrés."
	@echo "\n📁 Détails complets disponibles dans le dossier 'logs/' et dans test_results.txt."

# ---------------------------------------------------------------------------- #
# PHONY TARGETS
# ---------------------------------------------------------------------------- #
.PHONY: all clean fclean re debug valgrind test
