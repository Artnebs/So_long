# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anebbou <anebbou@student42.fr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/04 10:28:35 by anebbou           #+#    #+#              #
#    Updated: 2025/02/14 10:42:47 by anebbou          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#                                                     +:+ +:+         +:+      #
#    By: anebbou <anebbou@student42.fr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/04 10:28:35 by anebbou           #+#    #+#              #
#    Updated: 2025/02/14 10:41:31 by anebbou          ###   ########.fr        #
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

# ---------------------------------------------------------------------------- #
# COMPILER & FLAGS
# ---------------------------------------------------------------------------- #
CC         = gcc
CFLAGS     = -Wall -Wextra -Werror -g \
			 -I. \
			 -I$(LIBFT_DIR)/includes \
			 -I$(MLX_DIR)

# ---------------------------------------------------------------------------- #
# SOURCE & OBJECT FILES
# ---------------------------------------------------------------------------- #
SRCS       = check_path.c exit_game.c init_mlx.c load_textures.c \
			 main.c map_parsing.c map_validation.c player_movement.c \
			 monster_movement.c music.c texture_utils.c \
			 render_map.c load_default_map.c\
			 resize_hook.c init_window.c
OBJS       = $(SRCS:.c=.o)

# ---------------------------------------------------------------------------- #
# DEFAULT RULE
# ---------------------------------------------------------------------------- #
all: $(NAME)

# ---------------------------------------------------------------------------- #
# BUILD so_long
# ---------------------------------------------------------------------------- #
$(NAME): $(LIBFT) $(MLX_LIB) $(OBJS)
	@echo "Linking $(NAME)..."
	$(CC) $(CFLAGS) $(OBJS) \
		-L$(LIBFT_DIR) -lft \
		-L$(MLX_DIR) -lmlx -lm -lXext -lX11 \
		# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anebbou <anebbou@student42.fr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/04 10:28:35 by anebbou           #+#    #+#              #
#    Updated: 2025/02/14 10:41:31 by anebbou          ###   ########.fr        #
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

# ---------------------------------------------------------------------------- #
# COMPILER & FLAGS
# ---------------------------------------------------------------------------- #
CC         = gcc
CFLAGS     = -Wall -Wextra -Werror -g \
			 -I. \
			 -I$(LIBFT_DIR)/includes \
			 -I$(MLX_DIR)

# ---------------------------------------------------------------------------- #
# SOURCE & OBJECT FILES
# ---------------------------------------------------------------------------- #
SRCS       = check_path.c exit_game.c init_mlx.c load_textures.c \
			 main.c map_parsing.c map_validation.c player_movement.c \
			 monster_movement.c music.c texture_utils.c \
			 render_map.c load_default_map.c\
			 resize_hook.c init_window.c
OBJS       = $(SRCS:.c=.o)

# ---------------------------------------------------------------------------- #
# DEFAULT RULE
# ---------------------------------------------------------------------------- #
all: $(NAME)

# ---------------------------------------------------------------------------- #
# BUILD so_long
# ---------------------------------------------------------------------------- #
$(NAME): $(LIBFT) $(MLX_LIB) $(OBJS)
	@echo "Linking $(NAME)..."
	$(CC) $(CFLAGS) $(OBJS) \
		-L$(LIBFT_DIR) -lft \
		-L$(MLX_DIR) -lmlx -lm -lXext -lX11 \
				# **************************************************************************** #
		#                                                                              #
		#                                                         :::      ::::::::    #
		#    Makefile                                           :+:      :+:    :+:    #
		#                                                     +:+ +:+         +:+      #
		#    By: anebbou <anebbou@student42.fr>             +#+  +:+       +#+         #
		#                                                 +#+#+#+#+#+   +#+            #
		#    Created: 2025/02/04 10:28:35 by anebbou           #+#    #+#              #
		#    Updated: 2025/02/14 10:41:31 by anebbou          ###   ########.fr        #
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
		
		# ---------------------------------------------------------------------------- #
		# COMPILER & FLAGS
		# ---------------------------------------------------------------------------- #
		CC         = gcc
		CFLAGS     = -Wall -Wextra -Werror -g \
					 -I. \
					 -I$(LIBFT_DIR)/includes \
					 -I$(MLX_DIR)
		
		# ---------------------------------------------------------------------------- #
		# SOURCE & OBJECT FILES
		# ---------------------------------------------------------------------------- #
		SRCS       = check_path.c exit_game.c init_mlx.c load_textures.c \
					 main.c map_parsing.c map_validation.c player_movement.c \
					 monster_movement.c music.c texture_utils.c \
					 render_map.c load_default_map.c\
					 resize_hook.c init_window.c
		OBJS       = $(SRCS:.c=.o)
		
		# ---------------------------------------------------------------------------- #
		# DEFAULT RULE
		# ---------------------------------------------------------------------------- #
		all: $(NAME)
		
		# ---------------------------------------------------------------------------- #
		# BUILD so_long
		# ---------------------------------------------------------------------------- #
		$(NAME): $(LIBFT) $(MLX_LIB) $(OBJS)
			@echo "Linking $(NAME)..."
			$(CC) $(CFLAGS) $(OBJS) \
				-L$(LIBFT_DIR) -lft \
				-L$(MLX_DIR) -lmlx -lm -lXext -lX11 \
				# **************************************************************************** #
		#                                                                              #
		#                                                         :::      ::::::::    #
		#    Makefile                                           :+:      :+:    :+:    #
		#                                                     +:+ +:+         +:+      #
		#    By: anebbou <anebbou@student42.fr>             +#+  +:+       +#+         #
		#                                                 +#+#+#+#+#+   +#+            #
		#    Created: 2025/02/04 10:28:35 by anebbou           #+#    #+#              #
		#    Updated: 2025/02/14 10:41:31 by anebbou          ###   ########.fr        #
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
		
		# ---------------------------------------------------------------------------- #
		# COMPILER & FLAGS
		# ---------------------------------------------------------------------------- #
		CC         = gcc
		CFLAGS     = -Wall -Wextra -Werror -g \
					 -I. \
					 -I$(LIBFT_DIR)/includes \
					 -I$(MLX_DIR)
		
		# ---------------------------------------------------------------------------- #
		# SOURCE & OBJECT FILES
		# ---------------------------------------------------------------------------- #
		SRCS       = check_path.c exit_game.c init_mlx.c load_textures.c \
					 main.c map_parsing.c map_validation.c player_movement.c \
					 monster_movement.c music.c texture_utils.c \
					 render_map.c load_default_map.c\
					 resize_hook.c init_window.c
		OBJS       = $(SRCS:.c=.o)
		
		# ---------------------------------------------------------------------------- #
		# DEFAULT RULE
		# ---------------------------------------------------------------------------- #
		all: $(NAME)
		
		# ---------------------------------------------------------------------------- #
		# BUILD so_long
		# ---------------------------------------------------------------------------- #
		$(NAME): $(LIBFT) $(MLX_LIB) $(OBJS)
			@echo "Linking $(NAME)..."
			$(CC) $(CFLAGS) $(OBJS) \
				-L$(LIBFT_DIR) -lft \
				-L$(MLX_DIR) -lmlx -lm -lXext -lX11 \
				#    Updated: 2025/02/14 10:41:31 by anebbou          ###   ########.fr        #
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

# ---------------------------------------------------------------------------- #
# COMPILER & FLAGS
# ---------------------------------------------------------------------------- #
CC         = gcc
CFLAGS     = -Wall -Wextra -Werror -g \
			 -I. \
			 -I$(LIBFT_DIR)/includes \
			 -I$(MLX_DIR)

# ---------------------------------------------------------------------------- #
# SOURCE & OBJECT FILES
# ---------------------------------------------------------------------------- #
SRCS       = check_path.c exit_game.c init_mlx.c load_textures.c \
			 main.c map_parsing.c map_validation.c player_movement.c \
			 monster_movement.c music.c texture_utils.c \
			 render_map.c load_default_map.c\
			 resize_hook.c init_window.c
OBJS       = $(SRCS:.c=.o)

# ---------------------------------------------------------------------------- #
# DEFAULT RULE
# ---------------------------------------------------------------------------- #
all: $(NAME)

# ---------------------------------------------------------------------------- #
# BUILD so_long
# ---------------------------------------------------------------------------- #
$(NAME): $(LIBFT) $(MLX_LIB) $(OBJS)
	@echo "Linking $(NAME)..."
	$(CC) $(CFLAGS) $(OBJS) \
		-L$(LIBFT_DIR) -lft \
		-L$(MLX_DIR) -lmlx -lm -lXext -lX11 \
		-o $(NAME)

# ---------------------------------------------------------------------------- #
# COMPILE .c -> .o
# ---------------------------------------------------------------------------- #
%.o: %.c
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) -c $< -o $@

# ---------------------------------------------------------------------------- #
# BUILD LIBFT (CLONE IF NEEDED)
# ---------------------------------------------------------------------------- #
$(LIBFT):
	@if [ ! -d "$(LIBFT_DIR)" ]; then \
		echo "Cloning Libft repository..."; \
		git clone $(LIBFT_REPO) $(LIBFT_DIR); \
	fi
	@echo "Building Libft library..."
	make -C $(LIBFT_DIR)

# ---------------------------------------------------------------------------- #
# BUILD MINILIBX
# ---------------------------------------------------------------------------- #
$(MLX_LIB):
	@echo "Building MiniLibX..."
	make -C $(MLX_DIR)

# ---------------------------------------------------------------------------- #
# CLEAN RULES
# ---------------------------------------------------------------------------- #
clean:
	@echo "Cleaning object files..."
	rm -f $(OBJS)
	@if [ -d "$(LIBFT_DIR)" ]; then \
		make clean -C $(LIBFT_DIR); \
	fi
	@if [ -d "$(MLX_DIR)" ]; then \
		make clean -C $(MLX_DIR); \
	fi

fclean: clean
	@echo "Removing $(NAME)..."
	rm -f $(NAME)
	rm -rf Libft_GNL_Printf

re: fclean all

# ---------------------------------------------------------------------------- #
# DEBUG RULES
# ---------------------------------------------------------------------------- #
debug: fclean
	@echo "Compiling with debug symbols (-g)..."
	$(MAKE) CFLAGS="-Wall -Wextra -Werror -g" all

.PHONY: all clean fclean re debug
