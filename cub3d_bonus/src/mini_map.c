/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 16:52:03 by maroly            #+#    #+#             */
/*   Updated: 2022/04/04 11:41:10 by maroly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

int	is_pixel_around(t_gbl *gbl, int x, int y, t_square sq)
{
	int	dist;

	dist = sqrt((gbl->rc->posx * sq.length + sq.marge - sq.length / 6 - x)
			* (gbl->rc->posx * sq.length + sq.marge - sq.length / 6 - x)
			+ (gbl->rc->posy * sq.length + sq.marge - sq.length / 6 - y)
			* (gbl->rc->posy * sq.length + sq.marge - sq.length / 6 - y));
	if (dist <= 6 * sq.length)
		return (0);
	return (1);
}

void	print_square(t_square sq, t_gbl *gbl, int sign)
{
	int	x;
	int	y;

	y = -1;
	while (++y < sq.length)
	{
		x = -1;
		while (++x < sq.length)
		{
			if (sign == 0 && is_pixel_around(gbl, sq.x + x, sq.y + y, sq) == 0)
				put_pixel_image(gbl->mlx, (75 + sq.length / 4) + (sq.x + x)
					- (gbl->rc->posx * sq.length + sq.marge - sq.length / 6),
					(75 + sq.length / 4) + (sq.y + y) - (gbl->rc->posy
						* sq.length + sq.marge - sq.length / 6), sq.color);
			else if (sign == 1)
				put_pixel_image(gbl->mlx, 75 + x, 75 + y, sq.color);
		}
	}
}

int	find_ratio(void)
{
	double	r_mp;

	if (HEIGHT > WIDTH)
		r_mp = HEIGHT / 100;
	else
		r_mp = WIDTH / 100;
	return (r_mp);
}

void	print_map2(t_gbl *gbl, t_square *sq, int x, int y)
{
	sq->marge = HEIGHT * 0.025;
	sq->x = x * sq->r_sq + sq->marge;
	sq->y = y * sq->r_sq + sq->marge;
	sq->length = sq->r_sq;
	if (gbl->map[y][x] == '1')
	{
		sq->color = 0x000000;
		print_square(*sq, gbl, 0);
	}
	else if (gbl->map[y][x] == '2')
	{
		sq->color = 0x005F00;
		print_square(*sq, gbl, 0);
	}
	else if (gbl->map[y][x] != ' ')
	{
		sq->color = 0x696969;
		print_square(*sq, gbl, 0);
	}
}

void	print_map(t_gbl *gbl)
{
	int			y;
	int			x;
	t_square	sq;

	y = -1;
	sq.r_sq = find_ratio();
	while (gbl->map[++y])
	{
		x = -1;
		while (gbl->map[y][++x])
			print_map2(gbl, &sq, x, y);
	}
	sq.x = gbl->rc->posx * sq.r_sq + sq.marge;
	sq.y = gbl->rc->posy * sq.r_sq + sq.marge;
	sq.length = sq.r_sq / 2;
	sq.color = 0xFF0000;
	print_square(sq, gbl, 1);
}
