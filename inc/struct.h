/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 18:35:33 by hkovac            #+#    #+#             */
/*   Updated: 2022/03/31 16:47:33 by maroly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_color
{
	char **rgb;
	char *R;
	char *G;
	char *B;
	char *rg_hexa;
	char *rgb_hexa;
	char *rgb_dec;
	unsigned int color;
}	t_color;

typedef struct s_mlx
{
	void	*mlx;
	void	*mlx_win;
	void	*img;
	char	*addr;
	int		x_size;
	int		y_size;
	int		bpp;
	int		endian;
	int		line_length;
	int		texWidth;
	int		texHeight;
}	t_mlx;

typedef struct s_island
{
	int	col;
	int	row;
	int count;
}	t_island;

typedef struct s_rc
{
	int		mapX;
	int		mapY;
	double	posX;
	double	posY;
	double	sideX;
	double	sideY;
	double	deltaX;
	double	deltaY;
	int		side;
	double	perpWall;
	double	cameraX;
	double	rayDirX;
	double	rayDirY;
	double	dirX;
	double	dirY;
	double	planeX;
	double	planeY;
	float	speed;
	bool	is_running;
	int		hit;
	int		stepX;
	int		stepY;
	int		drawstart;
	int		drawend;
	int		lineheight;
	bool	has_dir_changed;
}	t_rc;

typedef struct s_gbl
{
	char	**map;
	char	**file;
	char	*tex_string[7];
	unsigned int sky;
	unsigned int floor;
	double	head;
	double	horizon;
	bool	is_mouse_hide;
	int count;
	int save_mapx;
	int save_mapy;
	t_mlx	*mlx;
	t_rc	*rc;
	t_mlx	**tex_tab;
	int	test;
}	t_gbl;

typedef struct s_pos
{
	int x;
	int y;
	int dx;
	int dy;
	int		signx;
	int		signy;
	int		error[2];
}	t_pos;

typedef struct s_square
{
	int	x;
	int	y;
	unsigned int	color;
	int	length;
	int marge;
}	t_square;


#endif