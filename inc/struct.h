/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkovac <hkovac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 18:35:33 by hkovac            #+#    #+#             */
/*   Updated: 2022/03/24 14:09:32 by hkovac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

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
}	t_mlx;

typedef struct s_island
{
	int	col;
	int	row;
	int count;
}	t_island;

typedef struct s_tex
{
	int	fd_NO;
	int	fd_SO;
	int	fd_WE;
	int	fd_EA;
}	t_tex;

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
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*f;
	char	*c;
	t_tex	*tex;
	t_mlx	*mlx;
	t_rc	*rc;
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

#endif