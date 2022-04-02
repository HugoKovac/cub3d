/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 18:35:33 by hkovac            #+#    #+#             */
/*   Updated: 2022/04/02 14:53:09 by maroly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_color
{
	char			**rgb;
	char			*r;
	char			*g;
	char			*b;
	char			*rg_hexa;
	char			*rgb_hexa;
	char			*rgb_dec;
	unsigned int	color;
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
	int		texwidth;
	int		texheight;
}	t_mlx;

typedef struct s_island
{
	int	col;
	int	row;
	int	count;
}	t_island;

typedef struct s_tex
{
	double			wallx;
	char			*tmp;
	unsigned int	color;
	int				what_tex;
	int				texx;
	double			step;
	double			texpos;
	int				texy;
}	t_tex;

typedef struct s_rc
{
	int		mapx;
	int		mapy;
	double	posx;
	double	posy;
	double	sidex;
	double	sidey;
	double	deltax;
	double	deltay;
	int		side;
	double	perpwall;
	double	camerax;
	double	raydirx;
	double	raydiry;
	double	dirx;
	double	diry;
	double	planex;
	double	planey;
	float	speed;
	bool	is_running;
	int		hit;
	int		stepx;
	int		stepy;
	int		drawstart;
	int		drawend;
	int		lineheight;
	bool	has_dir_changed;
}	t_rc;

typedef struct s_gbl
{
	char			**map;
	char			**file;
	char			*tex_string[8];
	unsigned int	sky;
	unsigned int	floor;
	double			head;
	double			horizon;
	bool			is_mouse_hide;
	int				count;
	double			posxcloud;
	double			posycloud;
	t_mlx			*mlx;
	t_rc			*rc;
	t_mlx			**tex_tab;
}	t_gbl;

typedef struct s_pos
{
	int	x;
	int	y;
	int	dx;
	int	dy;
	int	signx;
	int	signy;
	int	error[2];
}	t_pos;

typedef struct s_split
{
	size_t	i;
	size_t	string;
	char	**tab;
}	t_split;

typedef struct s_square
{
	int				x;
	int				y;
	unsigned int	color;
	int				length;
	int				marge;
	double			r_sq;
}	t_square;

#endif