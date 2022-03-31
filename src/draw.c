/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 16:47:25 by maroly            #+#    #+#             */
/*   Updated: 2022/03/31 18:25:23 by maroly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

void	init_mlx(t_mlx *mlx, int x, int y)
{
	mlx->x_size = x;
	mlx->y_size = y;
	mlx->mlx = mlx_init();
	mlx->mlx_win = mlx_new_window(mlx->mlx, x, y, "Cub3d");
	mlx->img = mlx_new_image(mlx->mlx, x, y);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bpp,
			&mlx->line_length, &mlx->endian);
}

void	put_pixel_image(t_mlx *mlx, int x, int y, unsigned int color)
{
	char	*pixel;

	if (y < mlx->y_size - 1 && x < mlx->x_size - 1 && x >= 0 && y >= 0)
	{
		pixel = mlx->addr + (y * mlx->line_length + x * (mlx->bpp / 8));
		*(unsigned int *)pixel = color;
	}
}

int	ter_dw(int f, int s)
{
	if (f < s)
		return (1);
	return (-1);
}

void	draw_line(t_pos beg, t_pos end, t_mlx *mlx, unsigned int color)
{
	t_pos	delta;
	t_pos	sign;
	t_pos	cur;

	delta.dx = abs(end.x - beg.x);
	delta.dy = abs(end.y - beg.y);
	sign.signx = ter_dw(beg.x, end.x);
	sign.signy = ter_dw(beg.y, end.y);
	sign.error[0] = delta.dx - delta.dy;
	cur = beg;
	while (cur.x != end.x || cur.y != end.y)
	{
		put_pixel_image(mlx, cur.x, cur.y, color);
		sign.error[1] = sign.error[0] * 2;
		if (sign.error[1] > -delta.dy)
		{
			sign.error[0] -= delta.dy;
			cur.x += sign.signx;
		}
		if (sign.error[1] < delta.dx)
		{
			sign.error[0] += delta.dx;
			cur.y += sign.signy;
		}
	}
}
