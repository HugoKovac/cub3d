SRC =	main.c \
		get_next_line.c get_next_line_u.c \
		parse_map.c \
		exit.c \
		utils_str.c utils_free.c \
		check_cub.c	\
		check_cub2.c	\
		count_island.c	\
		ray_casting.c \
		draw.c \
		open_texture.c \
		texturing.c \
		init_player.c \
		utils_mlx.c \
		controls.c \

NAME =	cub3d

UNAME :=	$(shell uname) 

CC = gcc

ifeq ($(UNAME), Darwin)
MLX_DIR = mlx_OG
MLX = libmlx.a 
FLAGS2 = -lmlx -framework OpenGL -framework Appkit
else
MLX_DIR = mlx
MLX = libmlx.a 
FLAGS2 = -lmlx -lm -lbsd -lX11 -lXext
endif

# MLX_DIR = mlx_OG
# MLX = libmlx.a 
# FLAGS2 = -lmlx -framework OpenGL -framework Appkit

# diff entre .a et .dylib
# .a = lib static, les fonctions utilisees sont directement ecrite dans le binaire
# .dylib = lib dynamique, les fonctions doivent etre chargees au momnent ou on lance le binaire

CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address

OBJ_DIR = obj
SRC_DIR = src
INC_DIR = inc

OBJ = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))
DPD = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.d))

.c.o:
	${CC} ${CFLAGS} -c$< -o ${<:.c=.o}

# -C faire make comme si on etait dans le dossier
# -j multisreder / ameliore la vitesse de compliation
# Pas de regle opti car makefile mlx pas compatible
all: $(NAME)

# permet de pouvoir comparer la derniere modification de la dep par rapport a la regle
# -L donner le nom du dossier / -l donner le nom le la lib
# loader path = ecrit le chemin de la mlx dans le binaire pour pouvoir la retrouver au moment ou on lance le binaire
$(NAME): $(OBJ)
		${CC} $(CFLAGS) -o $(NAME) $(OBJ) -L $(MLX_DIR) $(FLAGS2)

# si le .c est plus recent que le .o on rentre dans la regle
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | .gitignore
		make -C $(MLX_DIR)
		@mkdir -p $(OBJ_DIR)
		${CC} $(CFLAGS) -I $(INC_DIR) -I $(MLX_DIR) -c $< -o $@

.gitignore:
		@echo $(NAME) > .gitignore

clean:
	@rm -rf $(OBJ_DIR)

fclean:	clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re

# Utilise les .d (et ignore s'ils n'existe pas)
-include $(DPD)
