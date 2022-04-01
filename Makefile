SRC =	main.c \
		get_next_line.c get_next_line_u.c \
		parse_map.c \
		exit.c \
		utils_str.c utils_free.c \
		check_cub.c	check_cub2.c check_cub3.c	\
		check_handv.c	\
		count_island.c	count_island_utils.c	\
		ray_casting.c ray_casting_utils.c \
		draw.c \
		open_texture.c \
		texturing.c \
		init_player.c \
		utils_mlx.c \
		controls.c controls_wasd.c \
		ft_split.c	\
		ft_convert_base.c ft_convert_base2.c\


SRC_BONUS =	main.c \
		get_next_line.c get_next_line_u.c \
		parse_map.c \
		exit.c \
		utils_str.c utils_free.c \
		check_cub.c	check_cub2.c check_cub3.c	\
		check_handv.c	\
		count_island.c	count_island_utils.c	\
		ray_casting.c ray_casting_utils.c \
		draw.c \
		open_texture.c \
		texturing.c \
		init_player.c \
		utils_mlx.c \
		controls.c controls_wasd.c \
		ft_split.c	\
		ft_convert_base.c ft_convert_base2.c \
		mouse.c \
		mini_map.c \


NAME =	cub3d

NAME_BONUS =	cub3d_bo

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

MAND_MLX_DIR = $(addprefix cub3d_mand/, $(MLX_DIR))
BONUS_MLX_DIR = $(addprefix cub3d_bonus/, $(MLX_DIR))
MAND_MLX = $(addprefix cub3d_mand/, $(MLX))
BONUS_MLX = $(addprefix cub3d_bonus/, $(MLX))

CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address

OBJ_DIR = cub3d_mand/obj
SRC_DIR = cub3d_mand/src
INC_DIR = cub3d_mand/inc
OBJ_DIR_BONUS = cub3d_bonus/obj
SRC_DIR_BONUS = cub3d_bonus/src
INC_DIR_BONUS = cub3d_bonus/inc

OBJ_BONUS = $(addprefix $(OBJ_DIR_BONUS)/,$(SRC_BONUS:.c=.o))
OBJ = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))
DPD_BONUS = $(addprefix $(OBJ_DIR_BONUS)/,$(SRC_BONUS:.c=.d))
DPD = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.d))

.c.o:
	${CC} ${CFLAGS} -c$< -o ${<:.c=.o}

all: $(NAME)


$(NAME): $(OBJ)
		${CC} $(CFLAGS) -o $(NAME) $(OBJ) -L $(MAND_MLX_DIR) $(FLAGS2)


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | .gitignore
		make -C $(MAND_MLX_DIR)
		@mkdir -p $(OBJ_DIR)
		${CC} $(CFLAGS) -I $(INC_DIR) -I $(MAND_MLX_DIR) -c $< -o $@

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(OBJ_BONUS)
		${CC} $(CFLAGS) -o $(NAME_BONUS) $(OBJ_BONUS) -L $(BONUS_MLX_DIR) $(FLAGS2)

$(OBJ_DIR_BONUS)/%.o: $(SRC_DIR_BONUS)/%.c | .gitignore
		make -C $(BONUS_MLX_DIR)
		@mkdir -p $(OBJ_DIR_BONUS)
		${CC} $(CFLAGS) -I $(INC_DIR_BONUS) -I $(BONUS_MLX_DIR) -c $< -o $@

.gitignore:
		@echo $(NAME) > .gitignore

clean:
	@rm -rf $(OBJ_DIR)

fclean:	clean
	@rm -rf $(NAME)

clean_bonus:
	@rm -rf $(OBJ_DIR_BONUS)

fclean_bonus:	clean_bonus
	@rm -rf $(NAME_BONUS)

re: fclean all

re_bonus: fclean_bonus bonus

.PHONY: all, clean, fclean, re, bonus

-include $(DPD)
